/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   makeinfo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 03:42:35 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/06 03:45:15 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_info	info(void)
{
	t_info	img;


	img.mlx = NULL;
	img.win = NULL;
	img.ptr = NULL;
	img.pic = NULL;
	img.bit = 0;
	img.len = 0;
	img.endian = 0;
	return (img);
}

t_info	img_ptr(t_info	img)
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (img);
	win_ptr = mlx_new_window(mlx_ptr, 1000, 800, "FDF");
	if (!win_ptr)
		return (img);
	img_ptr = mlx_new_image(mlx_ptr, 1000, 800);
	img.mlx = mlx_ptr;
	img.win = win_ptr;
	img.ptr = img_ptr;
	return (img);
}

t_info	img_data(t_info img)
{
	int	bit;
	int	len;
	int	endian;

	img.pic = mlx_get_data_addr(img.ptr, &bit, &len, &endian);
	img.bit = bit;
	img.len = len;
	img.endian = endian;
	return (img);
}

int	handle_key_press(int keycode, void *param)
{
	if (keycode == 65307)
	{
		exit(0);
	}
	(void)param;
	return (0);
}

int	close_win(void *param)
{
	exit(0);
	(void)param;
	return (0);
}
