/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 23:45:02 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/16 03:16:48 by natakaha         ###   ########.fr       */
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

static t_map	**make_map(t_mapinfo *size, t_map **map)
{
	float	scale;
	int		ave_x;
	int		ave_y;

	if (!size->width || !size->height)
		return (NULL);
	if (!map)
		return (NULL);
	map = set_grid(*size, map, 1);
	scale = grid_scale(*size, map);
	map = set_grid(*size, map, scale);
	*size = color_info(map, *size);
	*size = search_edges(*size, map);
	ave_x = (size->min_x + size->max_x) / 2;
	ave_y = (size->min_y + size->max_y) / 2;
	map = move_grid(*size, map, WIDTH / 2 - ave_x, HEIGHT / 2 - ave_y);
	return (map);
}

t_all	make_all(t_info img, t_mapinfo *size, t_map **map)
{
	t_all	all;

	all.info = img;
	all.mapinfo = size;
	all.map = map;
	return (all);
}

void	free_and_close(t_map **map, t_info img, t_mapinfo size)
{
	free_map(map, size.width);
	mlx_destroy_image(img.mlx, img.ptr);
	mlx_destroy_window(img.mlx, img.win);
	mlx_destroy_display(img.mlx);
	free(img.mlx);
}

int	main(int argc, char **argv)
{
	t_info		img;
	t_mapinfo	size;
	t_map		**map;
	t_all		all;

	if (argc != 2)
		return (1);
	size = mapsize(argv[1]);
	if (!size.width || !size.height)
		return (1);
	img = correct_info();
	if (!img.mlx || !img.win || !img.ptr || !img.pic || !img.bit || !img.len)
		return (1);
	map = map_3d(argv[1], size);
	map = make_map(&size, map);
	if (!map)
		return (1);
	all = make_all(img, &size, map);
	connect_dots(img, map, size);
	mlx_put_image_to_window(img.mlx, img.win, img.ptr, 0, 0);
	mlx_hook(img.win, 17, 0, close_win, &all);
	mlx_key_hook(img.win, key_hooks, &all);
	mlx_loop(img.mlx);
	return (0);
}
