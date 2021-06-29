#include "fdf.h"

void	ft_exit(t_struct *as, char *str)
{
	printf("\n%s\n", str);
	free_split(as->map.map, number_of_split(as->map.map));
	free(as->map.point);
	exit(-1);
}

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
