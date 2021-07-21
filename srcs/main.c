#include "fdf.h"

int	main(int ac, char **av)
{
	t_struct	as;

	if (ac != 2)
		ft_exit(&as, "Wrong number of parameter.\n");
	parsing(&as, av[1]);
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
	mlx_loop_hook(as.vars.mlx, draw, &as);
	mlx_loop(as.vars.mlx);
	return (0);
}
