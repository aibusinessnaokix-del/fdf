/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 06:59:17 by naoki             #+#    #+#             */
/*   Updated: 2025/11/07 19:41:24 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	mapsize(char *file)
{
	int		fd;
	char	*line;
	int		count;
	t_map	size;

	size.x = 0;
	size.y = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (size);
	size.x = count_numbers(line);
	count = 0;
	while (line)
	{
		line = get_next_line(fd);
		count++;
		if (line && size.x != count_numbers(line))
			return (size);
	}
	size.y = count;
	return (size);
}

void	free_map(int **map, int x)
{
	while (x-- > 0)
		free(map[x]);
	free(map);
}

static int	**init_map(t_map size)
{
	int	**map;
	int	x;

	map = (int **)ft_calloc(sizeof(int *), size.x);
	if (!map)
		return (NULL);
	x = 0;
	while (x < size.x)
	{
		map[x] = (int *)ft_calloc(sizeof(int), size.y);
		if (!map[x])
			return (free_map(map, x), NULL);
		x++;
	}
	return (map);
}

int	**maping(char *file, t_map size)
{
	int		**map;
	int		fd;
	char	*line;
	int		x;
	int		y;

	map = init_map(size);
	if (!map)
		return (NULL);
	fd = open(file, O_RDONLY);
	y = 0;
	while (y < size.y)
	{
		line = get_next_line(fd);
		x = 0;
		while (x < size.x)
			map[x++][y] = ft_atol(&line);
		y++;
	}
	return (map);
}

t_map	highest(int **map, t_map size)
{
	int	x;
	int	y;
	int	high;

	x = 0;
	y = 0;
	high = map[0][0];
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			if (high < map[x][y])
				high = map[x][y];
			x++;
		}

		y++;
	}
	size.z = high;
	return (size);
}

//#include <stdio.h>

//int	main(int argc, char **argv)
//{
//	t_map	size;
//	int		**map;
//	int		x;
//	int		y;

//	if (argc < 2)
//		return (0);
//	if (argc > 2)
//		return (1);
//	size = mapsize(argv[1]);
//	if (!size.x || !size.y)
//		return (0);
//	map = maping(argv[1], size);
//	y = 0;
//	while (y < size.y)
//	{
//		x = 0;
//		while (x < size.x)
//			printf("%-3d", map[x++][y]);
//		printf("\n");
//		y++;
//	}
//}
