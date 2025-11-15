/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perth_3Dmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 06:59:17 by naoki             #+#    #+#             */
/*   Updated: 2025/11/16 02:38:55 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mapinfo	mapsize(char *file)
{
	int			fd;
	char		*line;
	int			count;
	t_mapinfo	size;

	size.width = 0;
	size.height = 0;
	fd = open(file, O_RDONLY);
	count = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (size.width == 0)
			size.width = count_numbers(line);
		else if (size.width != count_numbers(line))
			return (free(line), size);
		free(line);
		count++;
	}
	size.height = count;
	return (size);
}

static t_map	**calloc_map(t_mapinfo size)
{
	t_map	**map3d;
	int		x;

	map3d = (t_map **)ft_calloc(sizeof(t_map *), size.width);
	if (!map3d)
		return (NULL);
	x = 0;
	while (x < size.width)
	{
		map3d[x] = (t_map *)ft_calloc(sizeof(t_map), size.height);
		if (!map3d[x])
			return (free_map(map3d, x), NULL);
		x++;
	}
	return (map3d);
}

t_map	**map3d_module(int fd, t_mapinfo size, t_map **map3d, int y)
{
	char	*line;
	char	*tmp;
	int		x;

	line = get_next_line(fd);
	tmp = line;
	x = 0;
	while (x < size.width)
	{
		map3d[x][y].h = ft_atol(&tmp);
		map3d[x][y].color = read_color(&tmp);
		x++;
	}
	free(line);
	return (map3d);
}

t_map	**map_3d(char *file, t_mapinfo size)
{
	t_map	**map3d;
	int		fd;
	int		y;

	map3d = calloc_map(size);
	if (!map3d)
		return (NULL);
	fd = open(file, O_RDONLY);
	y = 0;
	while (y < size.height)
		map3d = map3d_module(fd, size, map3d, y++);
	get_next_line(fd);
	return (map3d);
}

void	free_map(t_map **map, int x)
{
	while (x-- > 0)
		free(map[x]);
	free(map);
}