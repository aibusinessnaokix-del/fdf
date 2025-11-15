/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pic_draw_lines1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:10:39 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/16 03:22:33 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned int	color(t_map tmp, t_mapinfo size)
{
	float	color;

	if (size.color > 0)
	{
		if (tmp.color >= 0)
			return (tmp.color);
		else
			return (0xFFFFFF);
	}
	else if (size.max_h || size.min_h)
		color = ((size.max_h - tmp.h) * 0xFFFFFF + (tmp.h - size.min_h)
					* 0xFF00FF) / (size.max_h - size.min_h);
	else
		color = 0xFFFFFF;
	return ((unsigned int)color);
}

static t_map	draw_line_x_module(t_map d1, t_map d2, t_map tmp,
		t_mapinfo size)
{
	if (d1.grid_y == d2.grid_y)
		tmp.grid_y = d1.grid_y;
	else
		tmp.grid_y = ((maxx(d1, d2).grid_x - tmp.grid_x) * minx(d1, d2).grid_y
				+ (tmp.grid_x - minx(d1, d2).grid_x) * maxx(d1, d2).grid_y)
			/ (maxx(d1, d2).grid_x - minx(d1, d2).grid_x);
	if (d1.h == d2.h)
		tmp.h = d1.h;
	else
		tmp.h = ((maxx(d1, d2).grid_x - tmp.grid_x) * minx(d1, d2).h
				+ (tmp.grid_x - minx(d1, d2).grid_x) * maxx(d1, d2).h)
			/ (maxx(d1, d2).grid_x - minx(d1, d2).grid_x);
	if (size.color > 0 && d1.color == d2.color)
		tmp.color = d1.color;
	else if (size.color > 0)
		tmp.color = ((maxx(d1, d2).grid_x - tmp.grid_x) * minx(d1, d2).color
				+ (tmp.grid_x - minx(d1, d2).grid_x) * maxx(d1, d2).color)
			/ (maxx(d1, d2).grid_x - minx(d1, d2).grid_x);
	return (tmp);
}

void	draw_line_x(t_map d1, t_map d2, t_info img, t_mapinfo size)
{
	t_map	tmp;
	char	*ptr;

	tmp.grid_x = minx(d1, d2).grid_x;
	tmp.grid_y = minx(d1, d2).grid_y;
	tmp.h = minx(d1, d2).h;
	tmp.color = minx(d1, d2).color;
	if (d1.color == -1)
		d1.color = 0xffffff;
	if (d2.color == -1)
		d2.color = 0xffffff;
	while (tmp.grid_x <= maxx(d1, d2).grid_x)
	{
		ptr = img.pic + tmp.grid_x * img.bit / 8 + tmp.grid_y * img.len;
		if (0 < tmp.grid_x && tmp.grid_x < WIDTH && 0 < tmp.grid_y
			&& tmp.grid_y < HEIGHT)
			*(unsigned int *)ptr = color(tmp, size);
		tmp.grid_x++;
		tmp = draw_line_x_module(d1, d2, tmp, size);
	}
}

static t_map	draw_line_y_module(t_map d1, t_map d2, t_map tmp,
		t_mapinfo size)
{
	if (d1.grid_x == d2.grid_x)
		tmp.grid_x = d1.grid_x;
	else
		tmp.grid_x = ((maxy(d1, d2).grid_y - tmp.grid_y) * miny(d1, d2).grid_x
				+ (tmp.grid_y - miny(d1, d2).grid_y) * maxy(d1, d2).grid_x)
			/ (maxy(d1, d2).grid_y - miny(d1, d2).grid_y);
	if (d1.h == d2.h)
		tmp.h = d1.h;
	else
		tmp.h = ((maxy(d1, d2).grid_y - tmp.grid_y) * miny(d1, d2).h
				+ (tmp.grid_y - miny(d1, d2).grid_y) * maxy(d1, d2).h)
			/ (maxy(d1, d2).grid_y - miny(d1, d2).grid_y);
	if (size.color > 0 && d1.color == d2.color)
		tmp.color = d1.color;
	else if (size.color > 0)
		tmp.color = ((maxy(d1, d2).grid_y - tmp.grid_y) * miny(d1, d2).color
				+ (tmp.grid_y - miny(d1, d2).grid_y) * maxy(d1, d2).color)
			/ (maxy(d1, d2).grid_y - miny(d1, d2).grid_y);
	return (tmp);
}

void	draw_line_y(t_map d1, t_map d2, t_info img, t_mapinfo size)
{
	t_map	tmp;
	char	*ptr;

	tmp.grid_x = miny(d1, d2).grid_x;
	tmp.grid_y = miny(d1, d2).grid_y;
	tmp.h = miny(d1, d2).h;
	tmp.color = miny(d1, d2).color;
	if (d1.color == -1)
		d1.color = 0xffffff;
	if (d2.color == -1)
		d2.color = 0xffffff;
	while (tmp.grid_y <= maxy(d1, d2).grid_y)
	{
		ptr = img.pic + tmp.grid_x * img.bit / 8 + tmp.grid_y * img.len;
		if (0 < tmp.grid_x && tmp.grid_x < WIDTH && 0 < tmp.grid_y
			&& tmp.grid_y < HEIGHT)
			*(unsigned int *)ptr = color(tmp, size);
		tmp.grid_y++;
		tmp = draw_line_y_module(d1, d2, tmp, size);
	}
}
