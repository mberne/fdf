#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "../libft/includes/libft.h"

# define ESC 53
# define SCALE 10

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

typedef struct s_map
{
	char	**map;
	int		num_row;
	int		num_col;
	int		num_point;
	t_point	*point;
}	t_map;

typedef struct s_struct
{
	t_vars	vars;
	t_data	data;
	t_map	map;
}	t_struct;

int		main(int ac, char **av);

void	parsing(t_struct *as, char *file);
void	take_map(t_struct *as, char *file, char **tmpmap);
void	take_points(t_struct *as);
void	fill_points(t_struct *as, char **line);

int		draw(t_struct *as);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

void	free_split(char **tab, int i);
int		number_of_split(char **tab);
int		ft_count(char const *s, char c);
int		ft_ishexa(char const *s);

int		close_win(int keycode, t_struct *as);
int		destroy_win(t_struct *as);
void	ft_exit(t_struct *as, char *str);

#endif