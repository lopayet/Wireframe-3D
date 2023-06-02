/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:15:47 by lopayet-          #+#    #+#             */
/*   Updated: 2023/02/08 14:49:46 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_wordlen(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*ft_strndup(const char *s1, size_t n)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * (n + 1));
	if (!res)
		return (0);
	i = 0;
	while (s1[i] && n)
	{
		res[i] = s1[i];
		n--;
		i++;
	}
	res[i] = 0;
	return (res);
}

static int	ft_split_len(char const *s, char c)
{
	int	words;
	int	in_word;
	int	i;

	i = 0;
	words = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] == c)
			in_word = 0;
		else
		{
			if (!in_word)
				words++;
			in_word = 1;
		}
		i++;
	}
	return (words + 1);
}

void	*ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	int		i;
	int		in_word;

	new = malloc(sizeof(char *) * ft_split_len(s, c));
	if (!new)
		return (0);
	in_word = 0;
	i = 0;
	while (*s)
	{
		if (*s == c)
			in_word = 0;
		else if (!in_word)
		{	
			new[i++] = ft_strndup(s, ft_wordlen(s, c));
			if (!new[i - 1])
				return (ft_free_split(new));
			in_word = 1;
		}
		s++;
	}
	new[i] = 0;
	return (new);
}
