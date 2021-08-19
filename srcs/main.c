/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 10:38:46 by mberne            #+#    #+#             */
/*   Updated: 2021/08/19 14:59:29 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	calc_px(t_map *map)
{
	int	i;

	i = 0;
	map->px = malloc(sizeof(t_px) * (map->num_point));
	while (i < map->num_point)
	{
		map->px[i].x = (map->point[i].x - map->point[i].y) * 2 * map->ratio
			+ map->shift_left;
		map->px[i].y = (map->point[i].x + map->point[i].y - map->point[i].z / 5)
			* map->ratio + map->shift_up;
		i++;
	}
}

void	scale_map(t_map *map)
{
	float	ratio_v;
	float	ratio_h;

	ratio_v = (float)V_RES
		/ ((map->point[map->highest].x + map->point[map->highest].y - map->point[map->highest].z / 5)
			- (map->point[map->lowest].x + map->point[map->lowest].y - 16 - map->point[map->lowest].z / 5));
	ratio_h = (float)H_RES
		/ ((map->point[map->num_col - 1].x - map->point[map->num_col - 1].y) * 2
			- (map->point[map->num_point - map->num_col].x
				- map->point[map->num_point - map->num_col].y - 8) * 2);
	if (ratio_v >= ratio_h)
		map->ratio = ratio_h;
	else
		map->ratio = ratio_v;
	map->shift_left = ((map->point[0].x - map->point[0].y) * 2
			- (map->point[map->num_point - map->num_col].x
				- map->point[map->num_point - map->num_col].y) * 2 + 8)
		* map->ratio;
	map->shift_up = 8 * map->ratio;
}

void	find_lowest_and_highest_point(t_map *map)
{
	int	i;
	int	lowest;
	int	highest;

	i = 0;
	lowest = (map->point[map->num_point - 1].x + map->point[map->num_point - 1].y - map->point[map->num_point - 1].z / 5);
	highest = (map->point[0].x + map->point[0].y - map->point[0].z / 5);
	while (i < map->num_point)
	{
		if ((map->point[i].x + map->point[i].y - map->point[i].z / 5) > highest)
		{
			highest = (map->point[i].x + map->point[i].y - map->point[i].z / 5);
			map->highest = i;
		}
		if ((map->point[i].x + map->point[i].y - map->point[i].z / 5) <= lowest)
		{
			lowest = (map->point[i].x + map->point[i].y - map->point[i].z / 5);
			map->lowest = i;
		}
		i++;
	}
}

void	parsing(t_struct *as, char *file)
{
	char	*tmpmap;

	tmpmap = NULL;
	take_map(as, file, &tmpmap);
	as->map.map = ft_split(tmpmap, '\n');
	if (!as->map.map)
		ft_exit(as, "Error\nMalloc error\n");
	free(tmpmap);
	as->map.num_row = number_of_split(as->map.map);
	take_points(as);
}

int	main(int ac, char **av)
{
	t_struct	as;

	ft_bzero(&as, sizeof(t_struct));
	if (ac != 2)
		ft_exit(&as, "Wrong number of parameter.\n");
	parsing(&as, av[1]);
	find_lowest_and_highest_point(&as.map);
	scale_map(&as.map);
	as.vars.mlx = mlx_init();
	if (!as.vars.mlx)
		ft_exit(&as, "MLX error.");
	as.vars.win = mlx_new_window(as.vars.mlx, H_RES, V_RES, "fdf");
	as.data.img = mlx_new_image(as.vars.mlx, H_RES, V_RES);
	if (!as.vars.win || !as.data.img)
		ft_exit(&as, "MLX error.");
	as.data.addr = mlx_get_data_addr(as.data.img, &as.data.bits_per_pixel,
			&as.data.line_length, &as.data.endian);
	if (!as.data.addr)
		ft_exit(&as, "MLX error.");
	mlx_hook(as.vars.win, 2, 0L, close_win, &as);
	mlx_hook(as.vars.win, 17, 0L, destroy_win, &as.vars);
	draw(&as);
	mlx_put_image_to_window(as.vars.mlx, as.vars.win, as.data.img, 0, 0);
	mlx_loop(as.vars.mlx);
	return (0);
}
