#include "fdf.h"

void	get_altitude_and_color(t_struct *as, char *point, int k)
{
	char	**data;

	if (ft_count(point, ',') == 0)
	{
		if (!ft_isnumber(point))
			ft_exit(as, "Error\nInvalide file\n");
		as->map.point[k].z = ft_atoi(point);
		as->map.point[k].color = 16777215;
	}
	else if (ft_count(point, ',') == 1)
	{
		data = ft_split(point, ',');
		if (!data[0] || !data[1])
			ft_exit(as, "Error\nMalloc error\n");
		if (!ft_isnumber(data[0]))
			ft_exit(as, "Error\nInvalide file\n");
		as->map.point[k].z = ft_atoi(data[0]);
		if (data[1][0] != '0' || data[1][1] != 'x')
			ft_exit(as, "Error\nInvalide file\n");
		data[1] += 2;
		if (!ft_ishexa(data[1]))
			ft_exit(as, "Error\nInvalide file\n");
		as->map.point[k].color = ft_atoi_base(data[1], "0123456789abcdef");
		if (as->map.point[k].color == 0)
			as->map.point[k].color = 16777215;
		data[1] -= 2;
		free_split(data, 2);
	}
	else
		ft_exit(as, "Error\nInvalide file\n");
}

void	fill_points(t_struct *as, char **line)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < as->map.num_row)
	{
		line = ft_split(as->map.map[i], ' ');
		if (!line)
			ft_exit(as, "Error\nMalloc error\n");
		j = 0;
		while (j < as->map.num_col)
		{
			as->map.point[k].x = j;
			as->map.point[k].y = i;
			get_altitude_and_color(as, line[j], k);
			j++;
			k++;
		}
		free_split(line, number_of_split(line));
		i++;
	}
}

void	take_points(t_struct *as)
{
	char	**line;

	line = ft_split(as->map.map[0], ' ');
	if (!line)
		ft_exit(as, "Error\nMalloc error\n");
	as->map.num_col = number_of_split(line);
	as->map.num_point = as->map.num_row * as->map.num_col;
	as->map.point = malloc(sizeof(t_point)
			* (as->map.num_point));
	free_split(line, number_of_split(line));
	fill_points(as, line);
}

void	take_map(t_struct *as, char *file, char **tmpmap)
{
	int		fd;
	int		ret;
	char	*line;

	fd = open(file, O_RDONLY);
	ret = 1;
	line = NULL;
	if (fd == -1)
		ft_exit(as, "Error\nFile failed to open\n");
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			ft_exit(as, "Error\nAn error occured while reading file\n");
		*tmpmap = ft_strjoin(*tmpmap, line);
		if (!tmpmap)
			ft_exit(as, "Error\nMalloc error\n");
		free(line);
		*tmpmap = ft_strjoin(*tmpmap, "\n");
		if (!tmpmap)
			ft_exit(as, "Error\nMalloc error\n");
	}
	if (close(fd) == -1)
		ft_exit(as, "Error\nFile failed to close\n");
}

void	parsing(t_struct *as, char *file)
{
	char	*tmpmap;

	tmpmap = NULL;
	take_map(as, file, &tmpmap);
	as->map.map = ft_split(tmpmap, '\n');
	if (!as->map.map)
		ft_exit(as, "Error\nMalloc error\n");
	free(tmpmap);
	as->map.num_row = number_of_split(as->map.map);
	take_points(as);
}