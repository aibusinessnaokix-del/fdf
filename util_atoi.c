/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:20:30 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/11 16:57:47 by natakaha         ###   ########.fr       */
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
	return (NONE);
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
		while (hex(*str) != NONE || *str == 'x' || *str == 'X')
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
		return (0);
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
			return (0);
		(*str)++;
	}
	while (**str == ' ' || (9 <= **str && **str <= 13))
		(*str)++;
	return ((int)n * sign);
}

int	ft_atohex(char **str)
{
	int	n;

	n = 0;
	while (**str == ' ' || (9 <= **str && **str <= 13))
		(*str)++;
	if (**str != ',')
		return (NONE);
	(*str)++;
	if (**str == '0' && ((*(*str + 1) == 'x') || (*(*str + 1) == 'X')))
		(*str) += 2;
	else if ('0' <= **str && **str <= '9')
		return (ft_atol(str));
	else
		return (ERROR);
	while (hex(**str) != NONE)
	{
		n = n * 16 + hex(**str);
		if (n > 16777216)
			return (ERROR);
		(*str)++;
	}
	while (**str == ' ' || (9 <= **str && **str <= 13))
		(*str)++;
	return (n);
}

// int	main(void)
//{
//	char	*str;

//	str = "123,0x0a 123,0x0a 123,0x0a 1,0x0a";
//	printf("%d\n", count_numbers(str));
//}
