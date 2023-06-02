/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:56:27 by lopayet-          #+#    #+#             */
/*   Updated: 2023/02/10 14:40:13 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	ft_isspace(char c)
{
	return ((c >= '\t' && c <= '\r')
		|| c == ' ');
}

int	ft_atoi(const char *str)
{
	long long int	res;
	int				sign;

	res = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	return ((int)(res * sign));
}
