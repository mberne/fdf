#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	draw(t_struct *as)
{
	int	i;

	i = 0;
	while (i < as->map.num_point)
	{
		my_mlx_pixel_put(&as->data, as->map.point[i].x * SCALE, as->map.point[i].y * SCALE, as->map.point[i].color);
		i++;
	}
	mlx_put_image_to_window(as->vars.mlx, as->vars.win, as->data.img, 0, 0);
	mlx_do_sync(as->vars.mlx);
	return (0);
}