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

int	draw(t_struct *as)
{
	int	i;

	i = 0;
	scale_map(&as->map);
	while (i < as->map.num_point)
	{
		if (as->map.point[i].z >= 0)
			my_mlx_pixel_put(&as->data, (as->map.point[i].x - as->map.point[i].y)
				* 2 * as->map.ratio + as->map.shift_left,
				(as->map.point[i].x + as->map.point[i].y - as->map.point[i].z / 10)
				* as->map.ratio + as->map.shift_up,
				as->map.point[i].color);
		else
			my_mlx_pixel_put(&as->data, (as->map.point[i].x - as->map.point[i].y)
				* 2 * as->map.ratio + as->map.shift_left,
				(as->map.point[i].x + as->map.point[i].y + as->map.point[i].z / 10)
				* as->map.ratio + as->map.shift_up,
				as->map.point[i].color);
		i++;
	}
	mlx_put_image_to_window(as->vars.mlx, as->vars.win, as->data.img, 0, 0);
	mlx_do_sync(as->vars.mlx);
	return (0);
}
