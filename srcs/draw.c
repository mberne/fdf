/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 10:39:49 by mberne            #+#    #+#             */
/*   Updated: 2021/08/18 11:30:47 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_segment(t_struct *as, t_px a, t_px b, int color)
{
	float	t;
	float	offset;
	t_px	ab;

	t = 0;
	ab.x = b.x - a.x;
	ab.y = b.y - a.y;
	offset = 1 / hypotf(ab.x, ab.y);
	while (t <= 1)
	{
		if (0 <= t * ab.x + a.x && t * ab.x + a.x < H_RES
			&& 0 <= t * ab.y + a.y && t * ab.y + a.y < V_RES)
			my_mlx_pixel_put(&as->data, t * ab.x + a.x, t * ab.y + a.y, color);
		t += offset;
	}
}

int	draw(t_struct *as)
{
	int	i;

	calc_px(&as->map);
	i = 0;
	while (i < as->map.num_point)
	{
		if (i < as->map.num_point - as->map.num_col)
			draw_segment(as, as->map.px[i], as->map.px[i + as->map.num_col],
				as->map.point[i].color);
		if ((i + 1) % as->map.num_col != 0)
			draw_segment(as, as->map.px[i], as->map.px[i + 1],
				as->map.point[i].color);
		i++;
	}
	return (0);
}
