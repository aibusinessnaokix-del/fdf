/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naoki <naoki@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-05 06:46:25 by naoki             #+#    #+#             */
/*   Updated: 2025-11-05 06:46:25 by naoki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_msize
{
	int	x;
	int	y;
}	t_msize;

/*get_next_line.c get_next_line_utils.c*/

char	*ft_strdup(const char *str);
char	*ft_strndup(const char *str, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strchr_len(const char *s, int c);
char	*get_next_line(int fd);

/*parth.c util_parth.c*/

int		count_numbers(char *str);
int 	ft_atol(char **str);
void	*ft_calloc(size_t nmemb, size_t size);

#endif