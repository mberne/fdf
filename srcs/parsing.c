/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberne <mberne@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 10:39:55 by mberne            #+#    #+#             */
/*   Updated: 2021/08/18 11:30:54 by mberne           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	altitude_color(t_struct *as, char *point, int k, int negativ)
{
	char	**data;

	data = ft_split(point, ',');
	if (!data[0] || !data[1])
		ft_exit(as, "Error\nMalloc error\n");
	if (data[0][0] == '-')
	{
		data[0]++;
		negativ = 1;
	}
	if (!ft_isnumber(data[0]))
		ft_exit(as, "Error\nInvalid file\n");
	if (negativ)
		data[0]--;
	as->map.point[k].z = ft_atoi(data[0]);
	if (data[1][0] != '0' || data[1][1] != 'x')
		ft_exit(as, "Error\nInvalid file\n");
	data[1] += 2;
	if (!ft_ishexa(data[1]))
		ft_exit(as, "Error\nInvalid file\n");
	as->map.point[k].color = ft_atoi_base(data[1], "0123456789abcdef");
	if (as->map.point[k].color == 0)
		as->map.point[k].color = 16777215;
	data[1] -= 2;
	free_split(data, 2);
}

void	get_altitude_and_color(t_struct *as, char *point, int k)
{
	int		negativ;

	negativ = 0;
	if (ft_count(point, ',') == 0)
	{
		if (point[0] == '-')
		{
			point++;
			negativ = 1;
		}
		if (!ft_isnumber(point))
			ft_exit(as, "Error\nInvalid file\n");
		if (negativ)
			point--;
		as->map.point[k].z = ft_atoi(point);
		as->map.point[k].color = 16777215;
	}
	else if (ft_count(point, ',') == 1)
		altitude_color(as, point, k, negativ);
	else
		ft_exit(as, "Error\nInvalid file\n");
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
	free_split(line, number_of_split(line));
	as->map.num_point = as->map.num_row * as->map.num_col;
	as->map.point = malloc(sizeof(t_point) * as->map.num_point);
	if (!as->map.point)
		ft_exit(as, "Error\nMalloc error\n");
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
