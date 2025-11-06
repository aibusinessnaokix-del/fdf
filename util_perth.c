/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_parth.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 07:51:15 by naoki             #+#    #+#             */
/*   Updated: 2025/11/05 23:16:23 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdint.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = c;
		i++;
	}
	return ((void *)p);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	lnb;
	void	*ptr;

	lnb = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if (SIZE_MAX / nmemb < size || (int)nmemb < 0 || (int)size < 0)
		return (NULL);
	ptr = malloc(lnb);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, lnb);
	return (ptr);
}

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
