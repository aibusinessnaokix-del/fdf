/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 23:45:02 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/06 11:35:59 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_info	img;
	t_map	size;
	int		**map;
	t_map	**display;

	if (argc != 2)
		return (1);
	img = info();
	img = img_ptr(img);
	if (!img.mlx)
		return (1);
	img = img_data(img);
	size = mapsize(argv[1]);
	map = maping(argv[1], size);
	display = make_display(size, map);
	connect_dots(img, display, size);
	mlx_put_image_to_window(img.mlx, img.win, img.ptr, 0, 0);
	mlx_key_hook(img.win, *handle_key_press, img.mlx);
	mlx_hook(img.win, 17, 0, *close_win, img.mlx);
	mlx_loop(img.mlx);
}
