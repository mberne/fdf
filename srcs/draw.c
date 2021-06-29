#include "fdf.h"

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