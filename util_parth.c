/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_parth.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naoki <naoki@student.42.fr>                #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-11-05 07:51:15 by naoki             #+#    #+#             */
/*   Updated: 2025-11-05 07:51:15 by naoki            ###   ########.fr       */
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
	if (SIZE_MAX / nmemb < size	||(int)nmemb < 0 || (int)size < 0)
		return (NULL);
	ptr = malloc(lnb);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, lnb);
	return (ptr);
}