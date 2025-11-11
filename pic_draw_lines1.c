/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pic_draw_lines1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:10:39 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/11 16:30:53 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned int	color(t_map tmp, t_size size)
{
	float	color;

	if (size.color == true)
	{
		if (tmp.color >= 0)
			return (tmp.color);
		else
			return (0xFFFFFF);
	}
	else if (size.z != 0)
		color = ((size.z - tmp.z) * 0xFFFFFF + tmp.z * 0xFF00FF) / size.z;
	else
		color = 0xFFFFFF;
	(void)tmp;
	(void)size;
	return ((unsigned int)color);
}

static t_map	draw_line_x_module(t_map d1, t_map d2, t_map tmp, t_size size)
{
	if (d1.y == d2.y)
		tmp.y = d1.y;
	else
		tmp.y = ((maxx(d1, d2).x - tmp.x) * minx(d1, d2).y + (tmp.x - minx(d1,
						d2).x) * maxx(d1, d2).y) / (maxx(d1, d2).x - minx(d1,
					d2).x);
	if (d1.z == d2.z)
		tmp.z = d1.z;
	else
		tmp.z = ((maxx(d1, d2).x - tmp.x) * minx(d1, d2).z + (tmp.x - minx(d1,
						d2).x) * maxx(d1, d2).z) / (maxx(d1, d2).x - minx(d1,
					d2).x);
	if (size.color > 0 && d1.color == d2.color)
		tmp.color = d1.color;
	else if (size.color == true)
		tmp.color = ((maxx(d1, d2).x - tmp.x) * minx(d1, d2).color + (tmp.x
					- minx(d1, d2).x) * maxx(d1, d2).color) / (maxx(d1, d2).x
				- minx(d1, d2).x);
	return (tmp);
}

void	draw_line_x(t_map d1, t_map d2, t_info img, t_size size)
{
	t_map	tmp;
	char	*ptr;

	tmp.x = minx(d1, d2).x;
	tmp.y = minx(d1, d2).y;
	tmp.z = minx(d1, d2).z;
	tmp.color = minx(d1, d2).color;
	if (d1.color == -1)
		d1.color = 0xffffff;
	if (d2.color == -1)
		d2.color = 0xffffff;
	while (tmp.x <= maxx(d1, d2).x)
	{
		ptr = img.pic + tmp.x * img.bit / 8 + tmp.y * img.len;
		if (0 < tmp.x && tmp.x < WIDTH && 0 < tmp.y && tmp.y < HEIGHT)
			*(unsigned int *)ptr = color(tmp, size);
		tmp.x++;
		tmp = draw_line_x_module(d1, d2, tmp, size);
	}
}

static t_map	draw_line_y_module(t_map d1, t_map d2, t_map tmp, t_size size)
{
	if (d1.x == d2.x)
		tmp.x = d1.x;
	else
		tmp.x = ((maxy(d1, d2).y - tmp.y) * miny(d1, d2).x + (tmp.y - miny(d1,
						d2).y) * maxy(d1, d2).x) / (maxy(d1, d2).y - miny(d1,
					d2).y);
	if (d1.z == d2.z)
		tmp.z = d1.z;
	else
		tmp.z = ((maxy(d1, d2).y - tmp.y) * miny(d1, d2).z + (tmp.y - miny(d1,
						d2).y) * maxy(d1, d2).z) / (maxy(d1, d2).y - miny(d1,
					d2).y);
	if (size.color > 0 && d1.color == d2.color)
		tmp.color = d1.color;
	else if (size.color == true)
		tmp.color = ((maxy(d1, d2).y - tmp.y) * miny(d1, d2).color + (tmp.y
					- miny(d1, d2).y) * maxy(d1, d2).color) / (maxy(d1, d2).y
				- miny(d1, d2).y);
	return (tmp);
}

void	draw_line_y(t_map d1, t_map d2, t_info img, t_size size)
{
	t_map	tmp;
	char	*ptr;

	tmp.x = miny(d1, d2).x;
	tmp.y = miny(d1, d2).y;
	tmp.z = miny(d1, d2).z;
	tmp.color = miny(d1, d2).color;
	if (d1.color == -1)
		d1.color = 0xffffff;
	if (d2.color == -1)
		d2.color = 0xffffff;
	while (tmp.y <= maxy(d1, d2).y)
	{
		ptr = img.pic + tmp.x * img.bit / 8 + tmp.y * img.len;
		if (0 < tmp.x && tmp.x < WIDTH && 0 < tmp.y && tmp.y < HEIGHT)
			*(unsigned int *)ptr = color(tmp, size);
		tmp.y++;
		tmp = draw_line_y_module(d1, d2, tmp, size);
	}
}
