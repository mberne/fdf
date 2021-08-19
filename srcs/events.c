/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 10:39:35 by mberne            #+#    #+#             */
/*   Updated: 2021/08/18 11:30:49 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_exit(t_struct *as, char *str)
{
	printf("%s", str);
	free_split(as->map.map, number_of_split(as->map.map));
	free(as->map.point);
	free(as->map.px);
	exit(-1);
}

int	close_win(int keycode, t_struct *as)
{
	if (keycode == ESC)
		ft_exit(as, "Window closed.\n");
	return (0);
}

int	destroy_win(t_struct *as)
{
	ft_exit(as, "Window closed.\n");
	return (0);
}
