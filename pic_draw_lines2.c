/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pic_draw_lines2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:24:06 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/16 02:43:04 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_line(t_map d1, t_map d2, t_info img, t_mapinfo size)
{
	int	dx;
	int	dy;

	dx = maxx(d1, d2).grid_x - minx(d1, d2).grid_x;
	dy = maxy(d1, d2).grid_y - miny(d1, d2).grid_y;
	if (dx == 0 && dy == 0)
		return ;
	if (dx >= dy)
		draw_line_x(d1, d2, img, size);
	else if (dy > dx)
		draw_line_y(d1, d2, img, size);
}

void	connect_dots(t_info img, t_map **display, t_mapinfo size)
{
	int	x;
	int	y;

	y = 0;
	while (y < size.height)
	{
		x = 0;
		while (x < size.width)
		{
			if (x + 1 < size.width)
				draw_line(display[x][y], display[x + 1][y], img, size);
			if (y + 1 < size.height)
				draw_line(display[x][y], display[x][y + 1], img, size);
			x++;
		}
		y++;
	}
}
