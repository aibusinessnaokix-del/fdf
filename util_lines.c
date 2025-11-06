/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 09:12:08 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/06 11:39:19 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	minx(t_map d1, t_map d2)
{
	if (d1.x > d2.x)
		return (d2);
	return (d1);
}

t_map	maxx(t_map d1, t_map d2)
{
	if (d1.x > d2.x)
		return (d1);
	return (d2);
}
t_map	miny(t_map d1, t_map d2)
{
	if (d1.y > d2.y)
		return (d2);
	return (d1);
}

t_map	maxy(t_map d1, t_map d2)
{
	if (d1.y > d2.y)
		return (d1);
	return (d2);
}