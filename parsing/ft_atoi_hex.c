/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 11:31:34 by lopayet-          #+#    #+#             */
/*   Updated: 2023/02/23 13:27:19 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

static char	*ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst);
}

static int	ft_char_in_base16(char to_find)
{
	char	base1[17];
	char	base2[17];
	int		i;

	ft_strcpy(base1, "0123456789abcdef");
	ft_strcpy(base2, "0123456789ABCDEF");
	i = 0;
	while (i < 16)
	{
		if (to_find == base1[i] || to_find == base2[i])
			return (i);
		i++;
	}
	return (-1);
}

static int	ft_get_str_sign(char *str)
{
	int	sign;

	sign = 0;
	while (ft_isspace(*str))
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign++;
		str++;
	}
	return (!(sign % 2) * 2 - 1);
}

int	ft_atoi_hex(char *str)
{
	int	res;
	int	sign_coef;
	int	base_len;
	int	i;

	base_len = 16;
	sign_coef = ft_get_str_sign(str);
	while (ft_isspace(*str))
		str++;
	res = 0;
	i = -1;
	while (ft_char_in_base16(str[++i]) != -1)
	{
		res *= base_len;
		res += ft_char_in_base16(str[i]);
	}
	return (res * sign_coef);
}
