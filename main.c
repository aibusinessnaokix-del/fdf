/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 23:45:02 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/11 16:54:29 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_info	correct_info(void)
{
	t_info	img;

	img = init_info();
	img = get_ptr(img);
	if (!img.mlx || !img.win || !img.ptr)
		return (init_info());
	img = img_data(img);
	return (img);
}

static t_map	**make_map(t_size *size, t_map **map3d)
{
	t_map	**pre_map2d;
	float	scale;
	t_map	**map2d;
	int		ave_x;
	int		ave_y;

	if (!size->x || !size->y)
		return (NULL);
	if (!map3d)
		return (NULL);
	pre_map2d = set_2dmap(*size, map3d, 1);
	if (!pre_map2d)
		return (free_map(map3d, size->x), NULL);
	scale = map2d_scale(*size, pre_map2d);
	map2d = set_2dmap(*size, map3d, scale);
	*size = highest(map3d, *size);
	*size = search_edges(*size, map2d);
	ave_x = (size->xmin + size->xmax) / 2;
	ave_y = (size->ymin + size->ymax) / 2;
	map2d = move_2dmap(*size, map2d, WIDTH / 2 - ave_x, HEIGHT / 2 - ave_y);
	free_map(pre_map2d, size->x);
	return (map2d);
}

t_all	make_all(t_info img, t_size *size, t_map **map2d, t_map **map3d)
{
	t_all	all;

	all.info = img;
	all.size = size;
	all.map2d = map2d;
	all.map3d = map3d;
	return (all);
}

void	free_and_close(t_map **map2d, t_map **map3d, t_info img, t_size size)
{
	if (map2d)
		free_map(map2d, size.x);
	if (map3d)
		free_map(map3d, size.x);
	mlx_destroy_image(img.mlx, img.ptr);
	mlx_destroy_window(img.mlx, img.win);
	mlx_destroy_display(img.mlx);
	free(img.mlx);
}

int	main(int argc, char **argv)
{
	t_info	img;
	t_size	size;
	t_map	**map3d;
	t_map	**map2d;
	t_all	all;

	if (argc != 2)
		return (1);
	size = mapsize(argv[1]);
	if (!size.x || !size.y)
		return (1);
	img = correct_info();
	if (!img.mlx || !img.win || !img.ptr || !img.pic || !img.bit || !img.len)
		return (1);
	map3d = map_3d(argv[1], size);
	map2d = make_map(&size, map3d);
	if (!map3d || !map2d)
		return (free_and_close(map2d, map3d, img, size), 1);
	all = make_all(img, &size, map2d, map3d);
	connect_dots(img, map2d, size);
	mlx_put_image_to_window(img.mlx, img.win, img.ptr, 0, 0);
	mlx_hook(img.win, 17, 0, close_win, img.mlx);
	mlx_key_hook(img.win, key_hooks, &all);
	mlx_loop(img.mlx);
	return (0);
}
