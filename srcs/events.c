/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 10:39:35 by mberne            #+#    #+#             */
/*   Updated: 2021/08/24 09:40:09 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_exit(t_struct *as, char *str, int status)
{
	printf("%s", str);
	free_split(as->map.map, number_of_split(as->map.map));
	free(as->map.point);
	free(as->map.px);
	if (status == -1)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

int	close_win(int keycode, t_struct *as)
{
	if (keycode == ESC)
		ft_exit(as, "Window closed.\n", 1);
	return (0);
}

int	destroy_win(t_struct *as)
{
	ft_exit(as, "Window closed.\n", 1);
	return (0);
}
