/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:10:39 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/07 20:41:51 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned int	color(t_map tmp, t_map size)
{
	float	color;

	if (size.z != 0)
		color = ((size.z - tmp.z) * 0xFFFFFF + tmp.z * 0xFF00FF) / size.z;
	else
		color = 0xFFFFFF;
	(void)tmp;
	(void)size;
	return ((unsigned int)color);
}

static void	line_x(t_map d1, t_map d2, t_info img, t_map size)
{
	t_map	tmp;
	char	*ptr;

	tmp.x = minx(d1, d2).x;
	tmp.y = minx(d1, d2).y;
	tmp.z = minx(d1, d2).z;
	while (tmp.x <= maxx(d1, d2).x)
	{
		ptr = img.pic + tmp.x * img.bit / 8 + tmp.y * img.len;
		*(unsigned int *)ptr = color(tmp, size);
		tmp.x++;
		tmp.y = ((maxx(d1, d2).x - tmp.x) * minx(d1, d2).y
				+ (tmp.x - minx(d1, d2).x) * maxx(d1, d2).y)
			/ (maxx(d1, d2).x - minx(d1, d2).x);
		if (d1.z == d2.z)
			tmp.z = d1.z;
		else
			tmp.z = ((maxx(d1, d2).x - tmp.x) * minx(d1, d2).z
					+ (tmp.x - minx(d1, d2).x) * maxx(d1, d2).z)
				/ (maxx(d1, d2).x - minx(d1, d2).x);
	}
}

static void	line_y(t_map d1, t_map d2, t_info img, t_map size)
{
	t_map	tmp;
	char	*ptr;

	tmp.x = miny(d1, d2).x;
	tmp.y = miny(d1, d2).y;
	tmp.z = miny(d1, d2).z;
	while (tmp.y <= maxy(d1, d2).y)
	{
		ptr = img.pic + tmp.x * img.bit / 8 + tmp.y * img.len;
		*(unsigned int *)ptr = color(tmp, size);
		tmp.y++;
		tmp.x = ((maxy(d1, d2).y - tmp.y) * miny(d1, d2).x
				+ (tmp.y - miny(d1, d2).y) * maxy(d1, d2).x)
			/ (maxy(d1, d2).y - miny(d1, d2).y);
		if (d1.z == d2.z)
			tmp.z = d1.z;
		else
			tmp.z = ((maxy(d1, d2).y - tmp.y) * miny(d1, d2).z
					+ (tmp.y - miny(d1, d2).y) * maxy(d1, d2).z)
				/ (maxy(d1, d2).y - miny(d1, d2).y);
	}
}

static void	draw_line(t_map d1, t_map d2, t_info img, t_map size)
{
	int	dx;
	int	dy;

	dx = maxx(d1, d2).x - minx(d1, d2).x;
	dy = maxy(d1, d2).y - miny(d1, d2).y;
	if (dy < 0)
		dy = -dy;
	if (dx >= dy)
		line_x(d1, d2, img, size);
	else if (dy > dx)
		line_y(d1, d2, img, size);
}

void	connect_dots(t_info img, t_map **display, t_map size)
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

//void	drawing(t_info img, t_map **display, t_map size, int color)
//{
//	char	*pixel_address;
//	int		x;
//	int		y;

//	x = 0;
//	y = 0;
//	while (y < size.y)
//	{
//		x = 0;
//		while (x < size.x)
//		{
//			if (display[x][y].x < 0 || display[x][y].x > 1000
//				|| display[x][y].y < 0 || display[x][y].y > 800)
//				return ;
//			pixel_address = img.pic + (display[x][y].y * img.len)
//				+ (display[x][y].x * img.bit / 8);
//			*(unsigned int *)pixel_address = color;
//			x++;
//		}
//		y++;
//	}
//}
