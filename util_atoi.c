/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:20:30 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/15 17:32:24 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	hex(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

int	count_numbers(char *str)
{
	int	count;

	count = 0;
	if (!str || !*str)
		return (0);
	while (*str)
	{
		while (*str == ' ' || (9 <= *str && *str <= 13))
			str++;
		if (*str == '+' || *str == '-')
			str++;
		if ('0' > *str || *str > '9')
			return (0);
		else
			count++;
		while ('0' <= *str && *str <= '9')
			str++;
		if (*str == ',')
			str++;
		while (hex(*str) != -1 || *str == 'x' || *str == 'X')
			str++;
		while (*str == ' ' || (9 <= *str && *str <= 13))
			str++;
	}
	return (count);
}

int	ft_atol(char **str)
{
	long long	n;
	int			sign;

	sign = 1;
	if (!str || !*str || !**str)
		return (INT_MIN);
	while (**str == ' ' || (9 <= **str && **str <= 13))
		(*str)++;
	if (**str == '+' || **str == '-')
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

int	read_color(char **str)
{
	int	n;

	n = 0;
	while (**str == ' ' || (9 <= **str && **str <= 13))
		(*str)++;
	if (**str != ',')
		return (-1);
	(*str)++;
	if (**str == '0' && ((*(*str + 1) == 'x') || (*(*str + 1) == 'X')))
		(*str) += 2;
	else
		return (ft_atol(str));
	while (hex(**str) != -1)
	{
		n = n * 16 + hex(**str);
		if (n > 16777216)
			return (-2);
		(*str)++;
	}
	while (**str == ' ' || (9 <= **str && **str <= 13))
		(*str)++;
	return (n);
}
