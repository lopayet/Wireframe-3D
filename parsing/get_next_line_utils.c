/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:02:05 by lopayet-          #+#    #+#             */
/*   Updated: 2022/11/29 11:07:15 by lopayet-         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_min(size_t n1, size_t n2)
{
	if (n1 < n2)
		return (n1);
	return (n2);
}

void	ft_bzero(void *s, size_t n)
{
	while (n)
	{
		*(char *)s = 0;
		s++;
		n--;
	}
}

char	*ft_strnchr(const char *s, int c, size_t n)
{
	char	byte;

	byte = (char) c;
	while (*s && *s != byte && n)
	{
		s++;
		n--;
	}
	if (*s == byte)
		return ((char *)s);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*res;
	int		i;

	res = malloc(n + 1);
	if (!res)
		return (0);
	i = 0;
	while (n)
	{
		res[i] = s1[i];
		i++;
		n--;
	}
	res[i] = 0;
	return (res);
}
