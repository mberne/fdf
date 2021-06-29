#include "fdf.h"

int	close_win(int keycode, t_struct *as)
{
	if (keycode == ESC)
		ft_exit(as, "Window closed.");
	return (0);
}

int	destroy_win(t_struct *as)
{
	ft_exit(as, "Window closed.");
	return (0);
}
