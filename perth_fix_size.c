/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perth_fix_size.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:28:34 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/11 06:24:01 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_size	compare_edge(t_size size, t_map tmp)
{
	if (size.xmax < tmp.x)
		size.xmax = tmp.x;
	else if (size.xmin > tmp.x)
		size.xmin = tmp.x;
	if (size.ymax < tmp.y)
		size.ymax = tmp.y;
	else if (size.ymin > tmp.y)
		size.ymin = tmp.y;
	return (size);
}

t_size	search_edges(t_size size, t_map **display)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	size.xmin = display[0][0].x;
	size.xmax = display[0][0].x;
	size.ymin = display[0][0].y;
	size.ymax = display[0][0].y;
	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			size = compare_edge(size, display[x][y]);
			y++;
		}
		x++;
	}
	return (size);
}

t_map	**move_2dmap(t_size size, t_map **display, int mx, int my)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			display[x][y].x = display[x][y].x + mx;
			display[x][y].y = display[x][y].y + my;
			y++;
		}
		x++;
	}
	return (display);
}

float	map2d_scale(t_size size, t_map **map2d)
{
	int		dx;
	int		dy;
	float	scale;

	size = search_edges(size, map2d);
	dx = size.xmax - size.xmin;
	dy = size.ymax - size.ymin;
	if (dx > WIDTH * 8 / 10 || dy > HEIGHT * 8 / 10)
		return (1);
	else if (dx == 0 || dy == 0)
		return (1);
	scale = min((float)(WIDTH * 8 / 10 / dx), (float)(HEIGHT * 8 / 10 / dy));
	return (scale);
}

// t_map	**make_2dmap(t_map size, int **map)
//{
//	t_map	**display;

//	display = set_display(size, map);
//	return (fix_display(size, display));

//}
