/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perth_3Dmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 06:59:17 by naoki             #+#    #+#             */
/*   Updated: 2025/11/11 16:42:34 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_size	mapsize(char *file)
{
	int		fd;
	char	*line;
	int		count;
	t_size	size;

	size.x = 0;
	size.y = 0;
	fd = open(file, O_RDONLY);
	count = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (size.x == 0)
			size.x = count_numbers(line);
		else if (size.x != count_numbers(line))
			return (free(line), size);
		free(line);
		count++;
	}
	size.y = count;
	return (size);
}

static t_map	**calloc_3dmap(t_size size)
{
	t_map	**map3d;
	int		x;

	map3d = (t_map **)ft_calloc(sizeof(t_map *), size.x);
	if (!map3d)
		return (NULL);
	x = 0;
	while (x < size.x)
	{
		map3d[x] = (t_map *)ft_calloc(sizeof(t_map), size.y);
		if (!map3d[x])
			return (free_map(map3d, x), NULL);
		x++;
	}
	return (map3d);
}

t_map	**map_3d_module(int fd, t_size size, t_map **map3d, int y)
{
	char	*line;
	char	*tmp;
	int		x;

	line = get_next_line(fd);
	if (!line)
		return (free_map(map3d, size.x), NULL);
	tmp = line;
	x = 0;
	while (x < size.x)
	{
		map3d[x][y].z = ft_atol(&tmp);
		map3d[x][y].color = ft_atohex(&tmp);
		if (map3d[x][y].color == ERROR)
			return (free(line), free_map(map3d, size.x), NULL);
		x++;
	}
	free(line);
	return (map3d);
}

t_map	**map_3d(char *file, t_size size)
{
	t_map	**map3d;
	int		fd;
	int		y;

	map3d = calloc_3dmap(size);
	if (!map3d)
		return (NULL);
	fd = open(file, O_RDONLY);
	y = 0;
	while (y < size.y)
		map3d = map_3d_module(fd, size, map3d, y++);
	get_next_line(fd);
	return (map3d);
}

void	free_map(t_map **map, int x)
{
	while (x-- > 0)
		free(map[x]);
	free(map);
}

//#include <stdio.h>

// int main(int argc, char **argv)
//{
//	t_map size;

//	size = mapsize(argv[1]);
//	printf("x:%d y:%d\n", size.x, size.y);
//}