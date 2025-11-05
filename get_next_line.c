/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 07:34:14 by natakaha          #+#    #+#             */
/*   Updated: 2025/10/30 20:39:02 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	*exec_before_n(char	*str)
{
	char	*display;

	if (str)
		if (!*str)
			return (NULL);
	if (ft_strchr_len(str, '\n') != -1)
		display = ft_strndup(str, (ft_strchr_len(str, '\n') + 1));
	else
		display = ft_strndup(str, (ft_strchr_len(str, '\0') + 1));
	if (display == NULL)
		return (NULL);
	return (display);
}

static char	*proceed_after_n(char	*str)
{
	char	*tmp;

	if (ft_strchr_len(str, '\n') == -1)
	{
		free(str);
		return (NULL);
	}
	tmp = ft_strndup(str + ft_strchr_len(str, '\n') + 1,
			ft_strchr_len(str, '\0') - ft_strchr_len(str, '\n'));
	free(str);
	return (tmp);
}

static char	*free_return_null(char *str)
{
	free(str);
	return (NULL);
}

static char	*read_extend_str(int fd, char *str)
{
	long long		count;
	char			*heap;
	char			*tmp;

	count = 42;
	while (ft_strchr_len(str, '\n') < 0 && count == 42)
	{
		heap = (char *)malloc(sizeof(char) * (42 + 1));
		if (!heap)
			return (NULL);
		count = read(fd, heap, 42);
		if (count >= 0)
		{
			heap[count] = '\0';
			tmp = str;
			str = ft_strjoin(str, heap);
			free(tmp);
		}
		free(heap);
	}
	if (count < 0)
		return (free_return_null(str));
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*display;

	if (fd == -1 || 42 == 0)
		return (NULL);
	if (ft_strchr_len(str, '\n') >= 0)
	{
		display = exec_before_n(str);
		str = proceed_after_n(str);
		return (display);
	}
	str = read_extend_str(fd, str);
	display = exec_before_n(str);
	str = proceed_after_n(str);
	return (display);
}

//#include <stdio.h>
//# include <fcntl.h>

//int	main(int argc, char **argv)
//{
//	int		fd;
//	char	*display;

//	fd = open(argv[1], O_RDONLY);
//	display = get_next_line(fd);
//	printf("%s", display);
//	free(display);
//	display = get_next_line(fd);
//	printf("%s", display);
//	free(display);
//	display = get_next_line(fd);
//	printf("%s", display);
//	free(display);
//	display = get_next_line(fd);
//	printf("%s", display);
//	free(display);
//	(void)argc;
//}
