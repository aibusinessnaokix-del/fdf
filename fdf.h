/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 06:46:25 by naoki             #+#    #+#             */
/*   Updated: 2025/11/06 11:39:40 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include "./minilibx_linux/mlx.h"
# include "./minilibx_linux/mlx_int.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_map
{
	int	x;
	int	y;
}	t_map;

typedef struct s_info
{
	void	*mlx;
	void	*win;
	void	*ptr;
	char	*pic;
	int		bit;
	int		len;
	int		endian;
}	t_info;


/*get_next_line.c get_next_line_utils.c*/

char	*ft_strdup(const char *str);
char	*ft_strndup(const char *str, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strchr_len(const char *s, int c);
char	*get_next_line(int fd);

/*perth.c util_perth.c*/

int		count_numbers(char *str);
int		ft_atol(char **str);
void	*ft_calloc(size_t nmemb, size_t size);
t_map	mapsize(char *file);
void	free_map(int **map, int x);
int		**maping(char *file, t_map size);

/*process.c*/
t_info	info(void);
t_info	img_ptr(t_info	img);
t_info	img_data(t_info img);
int		handle_key_press(int keycode, void *param);
int		close_win(void *param);

/*drawing.c util_drawing.c*/
void	drawing(t_info img, t_map **display, t_map size, int color);
t_map	**make_display(t_map size, int **map);
t_map	minx(t_map d1, t_map d2);
t_map	maxx(t_map d1, t_map d2);
t_map	miny(t_map d1, t_map d2);
t_map	maxy(t_map d1, t_map d2);
void	connect_dots(t_info img, t_map **display, t_map size);

#endif