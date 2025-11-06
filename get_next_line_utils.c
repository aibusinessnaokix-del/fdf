/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 07:34:17 by natakaha          #+#    #+#             */
/*   Updated: 2025/11/05 23:51:04 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_strchr_len(const char *s, int c)
{
	int	count;

	count = 0;
	if (!s)
		return (-1);
	if (c == '\0')
	{
		while (s[count])
			count++;
		return (count);
	}
	while (s[count])
	{
		if (s[count] == (char)c)
			return (count);
		count++;
	}
	return (-1);
}

static char	*allocate_char(char const *s1, char const *s2, char *joinstr)
{
	size_t	s1_count;
	size_t	s2_count;

	s1_count = 0;
	s2_count = 0;
	while (s1[s1_count])
	{
		joinstr[s1_count + s2_count] = s1[s1_count];
		s1_count++;
	}
	while (s2[s2_count])
	{
		joinstr[s1_count + s2_count] = s2[s2_count];
		s2_count++;
	}
	joinstr[s1_count + s2_count] = '\0';
	return (joinstr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*joinstr;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	total_len = ft_strchr_len(s1, '\0') + ft_strchr_len(s2, '\0') + 1;
	joinstr = (char *)malloc(sizeof(char) * total_len);
	if (joinstr == NULL)
		return (NULL);
	joinstr = allocate_char(s1, s2, joinstr);
	return (joinstr);
}

char	*ft_strndup(const char *str, size_t n)
{
	size_t	count;
	char	*dest;

	if (!str)
		return (NULL);
	if (n > (size_t)ft_strchr_len(str, '\0'))
		n = ft_strchr_len(str, '\0');
	dest = (char *)malloc(sizeof(char) * (n + 1));
	if (dest == NULL)
		return (NULL);
	count = 0;
	while (count < n)
	{
		dest[count] = str[count];
		count++;
	}
	dest[count] = '\0';
	return (dest);
}

char	*ft_strdup(const char *str)
{
	size_t	len;
	size_t	count;
	char	*dest;

	if (!str)
		return (NULL);
	len = ft_strchr_len(str, '\0');
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	count = 0;
	while (str[count])
	{
		dest[count] = str[count];
		count++;
	}
	dest[count] = '\0';
	return (dest);
}
