/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibx_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 01:29:33 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/16 02:57:18 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	translate(int keycode, void *param)
{
	t_map	move;
	t_all	*all;
	t_map	**map2d;

	all = (t_all *)param;
	move.grid_x = 0;
	move.grid_y = 0;
	if (keycode == 65361)
		move.grid_x = -5;
	if (keycode == 65362)
		move.grid_y = -5;
	if (keycode == 65363)
		move.grid_x = 5;
	if (keycode == 65364)
		move.grid_y = 5;
	if (65361 <= keycode && keycode <= 65364)
	{
		mlx_clear_window(all->info.mlx, all->info.win);
		ft_memset(all->info.pic, 0, WIDTH * HEIGHT * (all->info.bit / 8));
		map2d = move_grid(*(all->mapinfo), all->map, move.grid_x, move.grid_y);
		connect_dots(all->info, map2d, *(all->mapinfo));
		mlx_put_image_to_window(all->info.mlx, all->info.win, all->info.ptr, 0,
			0);
	}
	return (0);
}

// int	scale(int keycode, void *param)
//{
//	float	scale;
//	t_all	*all;
//	t_map	**map2d;

//	all = (t_all *)param;
//	scale = 1;
//	if (keycode == 43)
//		scale = 1.01;
//	if (keycode == 45)
//		scale = 0.99;
//	if (keycode == 42 || keycode == 45)
//	{
//		mlx_clear_window(all->info.mlx, all->info.win);
//		ft_memset(all->info.pic, 0, WIDTH * HEIGHT * (all->info.bit / 8));
//		map2d = set_2dmap(*(all->size), all->map3d, scale);
//		map2d = move_2dmap(*(all->size), map2d, 400, 300);
//		connect_dots(all->info, map2d, *(all->size));
//		mlx_put_image_to_window(all->info.mlx, all->info.win, all->info.ptr, 0,
			//0);
//	}
//	return (0);
//}

int	esc_quit(int keycode, void *param)
{
	t_all	*all;

	all = (t_all *)param;
	if (keycode == 65307)
	{
		free_and_close(all->map, all->info, *(all->mapinfo));
		exit(0);
	}
	(void)param;
	return (0);
}

int	close_win(void *param)
{
	t_all	*all;

	all = (t_all *)param;
	free_and_close(all->map, all->info, *(all->mapinfo));
	exit(0);
	(void)param;
	return (0);
}

int	key_hooks(int keycode, void *param)
{
	translate(keycode, param);
	esc_quit(keycode, param);
	return (0);
}
