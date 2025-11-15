/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perth_fix_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:28:34 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/15 23:23:18 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_mapinfo	compare_edge(t_mapinfo size, t_map tmp)
{
	if (size.max_x < tmp.grid_x)
		size.max_x = tmp.grid_x;
	else if (size.min_x > tmp.grid_x)
		size.min_x = tmp.grid_x;
	if (size.max_y < tmp.grid_y)
		size.max_y = tmp.grid_y;
	else if (size.min_y > tmp.grid_y)
		size.min_y = tmp.grid_y;
	return (size);
}

t_mapinfo	search_edges(t_mapinfo size, t_map **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	size.min_x = map[0][0].grid_x;
	size.max_x = map[0][0].grid_x;
	size.min_y = map[0][0].grid_y;
	size.max_y = map[0][0].grid_y;
	while (x < size.width)
	{
		y = 0;
		while (y < size.height)
		{
			size = compare_edge(size, map[x][y]);
			y++;
		}
		x++;
	}
	return (size);
}

t_map	**move_grid(t_mapinfo size, t_map **map, int mx, int my)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < size.width)
	{
		y = 0;
		while (y < size.height)
		{
			map[x][y].grid_x = map[x][y].grid_x + mx;
			map[x][y].grid_y = map[x][y].grid_y + my;
			y++;
		}
		x++;
	}
	return (map);
}

float	grid_scale(t_mapinfo size, t_map **map)
{
	int		dx;
	int		dy;
	float	scale;

	size = search_edges(size, map);
	dx = size.max_x - size.min_x;
	dy = size.max_y - size.min_y;
	if (dx > WIDTH * 0.8 || dy > HEIGHT * 0.8)
		return (1);
	else if (dx == 0 || dy == 0)
		return (1);
	scale = min((float)(WIDTH * 0.8 / dx), (float)(HEIGHT * 0.8 / dy));
	return (scale);
}
