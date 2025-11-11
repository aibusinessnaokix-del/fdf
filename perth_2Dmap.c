/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perth_2Dmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:41:06 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/11 14:55:20 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_map	**calloc_2dmap(t_size size)
{
	t_map	**map2d;
	int		x;

	map2d = (t_map **)ft_calloc(sizeof(t_map *), size.x);
	if (!map2d)
		return (NULL);
	x = 0;
	while (x < size.x)
	{
		map2d[x] = (t_map *)ft_calloc(sizeof(t_map), size.y);
		if (!map2d[x])
			return (free_map(map2d, x), NULL);
		x++;
	}
	return (map2d);
}

static t_map	projection(int x, int y, t_map dot, float scale)
{
	t_map	pixel;

	pixel.x = (x - y) * cos(0.523599) * scale * 5;
	pixel.y = ((x + y) * sin(0.523599) - dot.z) * scale * 5;
	pixel.z = dot.z;
	pixel.color = dot.color;
	return (pixel);
}

t_map	**set_2dmap(t_size size, t_map **map3d, float scale)
{
	int		x;
	int		y;
	t_map	**map2d;

	x = 0;
	y = 0;
	map2d = calloc_2dmap(size);
	if (!map2d)
		return (NULL);
	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			map2d[x][y] = projection(x, y, map3d[x][y], scale);
			y++;
		}
		x++;
	}
	return (map2d);
}

t_size	highest(t_map **map, t_size size)
{
	int	x;
	int	y;
	int	high;
	int	cflag;

	x = 0;
	y = 0;
	cflag = 0;
	high = map[0][0].z;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			if (high < map[x][y].z)
				high = map[x][y].z;
			if (map[x][y].color >= 0)
				cflag = 1;
			x++;
		}
		y++;
	}
	size.color = cflag;
	size.z = high;
	return (size);
}
