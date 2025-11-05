/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naoki <naoki@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-05 06:59:17 by naoki             #+#    #+#             */
/*   Updated: 2025-11-05 06:59:17 by naoki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_numbers(char *str)
{
	int	count;

	count = 0;
	if (!str || !*str)
		return (false);
	while (*str)
	{
		while (*str == ' ' || (9 <= *str && *str <= 13))
			str++;
		if (*str == '+' || *str == '-')
			str++;
		if ('0' > *str || *str > '9')
			return (false);
		else
			count++;
		while ('0' <= *str && *str <= '9')
			str++;
		while (*str == ' ' || (9 <= *str && *str <= 13))
			str++;
	}
	return (count);
}

int	ft_atol(char **str)
{
	long long		n;
	int				sign;

	sign = 1;
	if (!str || !*str || !**str)
		return (INT_MIN);
	while (**str == ' ' || (9 <= **str && **str <= 13))
		(*str)++;
	if (**str == '+' || **str == '-' )
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	n = 0;
	while ('0' <= **str && **str <= '9')
	{
		n = n * 10 + (**str - '0');
		if ((sign > 0 && INT_MAX < n) || (sign < 0 && INT_MAX < n - 1))
			return (INT_MIN);
		(*str)++;
	}
	while (**str == ' ' || (9 <= **str && **str <= 13))
		(*str)++;
	return ((int)n * sign);
}

t_msize	mapsize(char *file)
{
	int		fd;
	char	*line;
	int		count;
	t_msize	size;
	
	size.x = 0;
	size.y = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (size);
	size.x = count_numbers(line);
	count = 0;
	while  (line)
	{	
		line = get_next_line(fd);
		count++;
		if (line && size.x != count_numbers(line))
			return (size);
	}
	size.y = count;
	return (size);
}

void	free_map(int **map, int x)
{
	while (x-- > 0)
		free(map[x]);
	free(map);
}

static int	**make_map(t_msize size)
{
	int **map;
	int	x;

	map = (int **)ft_calloc(sizeof(int *) , size.x);
	if (!map)
		return (NULL);
	x = 0;
	while (x < size.x)
	{
		map[x] = (int *)ft_calloc(sizeof(int) , size.y);
		if (!map[x])
			return (free_map(map, x), NULL);
		x++;
	}
	return (map);
}

int	**maping(char *file, t_msize size)
{
	int		**map;
	int		fd;
	char	*line;
	int		x;
	int		y;

	map = make_map(size);
	fd = open(file, O_RDONLY);
	y = 0;
	while (y < size.y)
	{
		line = get_next_line(fd);
		x = 0;
		while (x < size.x)
			map[x++][y] = ft_atol(&line);
		y++;
	}
	return (map);
}

#include <stdio.h>

int	main(int argc, char **argv)
{
	t_msize	size;
	int		**map;
	int		x;
	int		y;

	if (argc < 2)
		return (0);
	if (argc > 2)
		return (1);
	size = mapsize(argv[1]);
	if (!size.x || !size.y)
		return (0);
	map = maping(argv[1], size);
	y = 0;
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
			printf("%-3d", map[x++][y]);
		printf("\n");
		y++;
	}
}