/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 03:47:28 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/06 11:12:01 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_display(t_map **display, int x)
{
	while (x--)
		free(display[x]);
	free(display);
}

static t_map	**init_display(t_map size)
{
	t_map	**display;
	int		x;

	display = (t_map **)ft_calloc(sizeof(t_map *), size.x);
	if (!display)
		return (NULL);
	x = 0;
	while (x < size.x)
	{
		display[x] = (t_map *)ft_calloc(sizeof(t_map), size.y);
		if (!display[x])
			return (free_display(display, x), NULL);
		x++;
	}
	return (display);
}

static t_map	translate(int x, int y, int z)
{
	t_map	pixel;

	pixel.x = (x - y) * cos(0.523599) * 20 + 400;
	pixel.y = ((x + y) * sin(0.523599) - z) * 20 + 300;
	return (pixel);
}

t_map	**make_display(t_map size, int **map)
{
	int		x;
	int		y;
	t_map	**display;

	x = 0;
	y = 0;
	display = init_display(size);
	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			display[x][y] = translate(x, y, map[x][y]);
			y++;
		}
		x++;
	}
	return (display);
}

//#include <stdio.h>

//int	main(int argc, char **argv)
//{
//	t_info	img;
//	t_map	size;
//	int		**map;
//	t_map	**display;
//	int		x;
//	int		y;

//	if (argc != 2)
//		return (1);
//	img = info();
//	img = img_ptr(img);
//	if (!img.mlx)
//		return (1);
//	img = img_data(img);
//	size = mapsize(argv[1]);
//	map = maping(argv[1], size);
//	display = make_display(size, map);
//	y = 0;
//	while (y < size.y)
//	{
//		x = 0;
//		while (x < size.x)
//		{
//			printf("x: %d y : %d\n", display[x][y].x, display[x][y].y);
//			x++;
//		}
//		y++;
//	}
//}
