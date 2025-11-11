/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 06:46:25 by naoki             #+#    #+#             */
/*   Updated: 2025/11/11 17:02:15 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./minilibx-linux/mlx.h"
# include "./minilibx-linux/mlx_int.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1000
# define HEIGHT 800
# define NONE -1
# define ERROR -2
# define ESC 65307
# define RIGHT 65361
# define UP 65362
# define LEFT 65363
# define DOWN 65364

typedef struct s_map
{
	float	z;
	int		x;
	int		y;
	int		color;
}			t_map;

typedef struct s_size
{
	int		x;
	int		y;
	int		z;
	int		xmax;
	int		xmin;
	int		ymax;
	int		ymin;
	int		color;
}			t_size;

typedef struct s_info
{
	void	*mlx;
	void	*win;
	void	*ptr;
	char	*pic;
	int		bit;
	int		len;
	int		endian;
}			t_info;

typedef struct s_all
{
	t_map	**map2d;
	t_map	**map3d;
	t_size	*size;
	t_info	info;
}			t_all;

/*util_atoi.c 4*/
int			count_numbers(char *str);
int			ft_atol(char **str);
int			ft_atohex(char **str);

/*util_calloc.c 2*/
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memset(void *s, int c, size_t n);

/*util_maxmin.c 5*/
t_map		minx(t_map d1, t_map d2);
t_map		maxx(t_map d1, t_map d2);
t_map		miny(t_map d1, t_map d2);
t_map		maxy(t_map d1, t_map d2);
float		min(float i1, float i2);

/*util_gnl.c 5*/
char		*get_next_line(int fd);

/*util_gnl_util 5*/
int			ft_strchr_len(const char *s, int c);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strndup(const char *str, size_t n);
char		*ft_strdup(const char *str);

/*minilibX.c 5*/
t_info		init_info(void);
t_info		get_ptr(t_info img);
t_info		img_data(t_info img);

/*minilibx_hooks.c*/
int			translate(int keycode, void *param);
int			esc_quit(int keycode, void *param);
int			close_win(void *param);
int			scale(int keycode, void *param);
int			key_hooks(int keycode, void *param);

/*perth_3Dmap.c 4*/
t_size		mapsize(char *file);
t_map		**map_3d(char *file, t_size size);
void		free_map(t_map **map, int x);

/*perth_2dmap.c 4*/
t_map		**set_2dmap(t_size size, t_map **map3d, float scale);
t_size		highest(t_map **map3d, t_size size);

/*perth_fix_size.c 4*/
t_map		**move_2dmap(t_size size, t_map **display, int ave_x, int ave_y);
float		map2d_scale(t_size size, t_map **map2d);
t_size		search_edges(t_size size, t_map **display);

/*pic_draw_lines1.c 5*/
void		draw_line_x(t_map d1, t_map d2, t_info img, t_size size);
void		draw_line_y(t_map d1, t_map d2, t_info img, t_size size);

/*pic_draw_lines2.c 2*/
void		connect_dots(t_info img, t_map **display, t_size size);

/*main.c*/
void		move_and_projection(t_info img, t_size size, t_map **map2d,
				t_map move);
void		free_and_close(t_map **map2d, t_map **map3d, t_info img,
				t_size size);

#endif