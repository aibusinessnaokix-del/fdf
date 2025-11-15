/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perth_2Dmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:41:06 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/16 03:13:06 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_map	projection(int x, int y, t_map dot, float scale)
{

	dot.grid_x = (x - y) * cos(R30) * scale * 5;
	dot.grid_y = ((x + y) * sin(R30) - dot.h) * scale * 5;
	return (dot);
}

t_map	**set_grid(t_mapinfo mapinfo, t_map **map, float scale)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (!map)
		return (NULL);
	while (x < mapinfo.width)
	{
		y = 0;
		while (y < mapinfo.height)
		{
			map[x][y] = projection(x, y, map[x][y], scale);
			y++;
		}
		x++;
	}
	return (map);
}

t_mapinfo	color_info(t_map **map, t_mapinfo mapinfo)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	mapinfo.max_h = map[0][0].h;
	mapinfo.color = 0;
	while (y < mapinfo.height)
	{
		x = 0;
		while (x < mapinfo.width)
		{
			if (mapinfo.max_h < map[x][y].h)
				mapinfo.max_h = map[x][y].h;
			if (mapinfo.min_h > map[x][y]. h)
				mapinfo.min_h = map[x][y].h;
			if (map[x][y].color >= 0)
				mapinfo.color = 1;
			x++;
		}
		y++;
	}
	return (mapinfo);
}
