/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 10:40:12 by mberne            #+#    #+#             */
/*   Updated: 2021/08/24 10:10:47 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "../libft/includes/libft.h"

# define ESC 53
# define H_RES 2560
# define V_RES 1440

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_point;

typedef struct s_px
{
	float	x;
	float	y;
}	t_px;

typedef struct s_map
{
	char	**map;
	int		num_row;
	int		num_col;
	int		num_point;
	int		lowest;
	int		highest;
	float	ratio;
	float	shift_left;
	float	shift_up;
	t_point	*point;
	t_px	*px;
}	t_map;

typedef struct s_struct
{
	t_vars	vars;
	t_data	data;
	t_map	map;
}	t_struct;

int		main(int ac, char **av);
void	parsing(t_struct *as, char *file);
void	find_lowest_and_highest_point(t_map *map);
void	scale_map(t_map *map);
void	calc_px(t_map *map);

void	take_map(t_struct *as, char *file, char **tmpmap);
void	take_points(t_struct *as);
void	fill_points(t_struct *as, char **line);
void	get_altitude_and_color(t_struct *as, char *point, int k);
void	altitude_color(t_struct *as, char *point, int k, int negativ);

int		draw(t_struct *as);
void	draw_segment(t_struct *as, t_px a, t_px b, int color);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

void	free_split(char **tab, int i);
int		number_of_split(char **tab);
int		ft_count(char const *s, char c);
int		ft_ishexa(char const *s);

int		close_win(int keycode, t_struct *as);
int		destroy_win(t_struct *as);
void	ft_exit(t_struct *as, char *str, int status);

#endif