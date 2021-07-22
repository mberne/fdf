#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	scale_map(t_map *map)
{
	float	ratio_v;
	float	ratio_h;

	ratio_v = (float)V_RES
		/ (map->point[map->num_point - 1].x + map->point[map->num_point - 1].y
			- (map->point[0].x + map->point[0].y) + 8);
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

void	calc_px(t_map *map)
{
	int	i;

	i = 0;
	map->px = malloc(sizeof(t_px) * (map->num_point));
	while (i < map->num_point)
	{
		map->px[i].x = (map->point[i].x - map->point[i].y) * 2 * map->ratio
			+ map->shift_left;
		map->px[i].y = (map->point[i].x + map->point[i].y - map->point[i].z)
			* map->ratio + map->shift_up;
		i++;
	}
}

int	draw(t_struct *as)
{
	int	i;

	i = 0;
	calc_px(&as->map);
	while (i < as->map.num_point)
	{
		my_mlx_pixel_put(&as->data, as->map.px[i].x, as->map.px[i].y,
			as->map.point[i].color);
		i++;
	}
	mlx_put_image_to_window(as->vars.mlx, as->vars.win, as->data.img, 0, 0);
	mlx_do_sync(as->vars.mlx);
	return (0);
}
