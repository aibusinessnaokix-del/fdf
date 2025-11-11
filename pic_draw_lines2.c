/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pic_draw_lines2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:24:06 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/11 15:27:45 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_line(t_map d1, t_map d2, t_info img, t_size size)
{
	int	dx;
	int	dy;

	dx = maxx(d1, d2).x - minx(d1, d2).x;
	dy = maxy(d1, d2).y - miny(d1, d2).y;
	if (dy < 0)
		dy = -dy;
	if (dx == 0 && dy == 0)
		return ;
	if (dx >= dy)
		draw_line_x(d1, d2, img, size);
	else if (dy > dx)
		draw_line_y(d1, d2, img, size);
}

void	connect_dots(t_info img, t_map **display, t_size size)
{
	int	x;
	int	y;

	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			if (x + 1 < size.x)
				draw_line(display[x][y], display[x + 1][y], img, size);
			if (y + 1 < size.y)
				draw_line(display[x][y], display[x][y + 1], img, size);
			x++;
		}
		y++;
	}
}
