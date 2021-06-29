#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_exit(t_struct *as, char *str)
{
	printf("\n%s\n", str);
	free_split(as->map.map, number_of_split(as->map.map));
	free(as->map.point);
	exit(-1);
}

int	main(int ac, char **av)
{
	t_struct	as;

	(void)av;
	if (ac != 2)
		ft_exit(&as, "Wrong number of parameter.\n");
	as.vars.mlx = mlx_init();
	if (!as.vars.mlx)
		ft_exit(&as, "MLX error.");
	as.vars.win = mlx_new_window(as.vars.mlx, 1000, 1000, "fdf");
	as.data.img = mlx_new_image(as.vars.mlx, 1000, 1000);
	if (!as.vars.win || !as.data.img)
		ft_exit(&as, "MLX error.");
	as.data.addr = mlx_get_data_addr(as.data.img, &as.data.bits_per_pixel,
			&as.data.line_length, &as.data.endian);
	if (!as.data.addr)
		ft_exit(&as, "MLX error.");
	parsing(&as, av[1]);
	draw(&as);
	mlx_hook(as.vars.win, 2, 0L, close_win, &as);
	mlx_hook(as.vars.win, 17, 0L, destroy_win, &as.vars);
	// mlx_loop_hook(as.vars.mlx, draw, &as);
	mlx_loop(as.vars.mlx);
	return (0);
}
