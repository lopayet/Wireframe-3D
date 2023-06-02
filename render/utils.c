/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:30:41 by lopayet-          #+#    #+#             */
/*   Updated: 2023/02/10 14:38:41 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	is_pixel_outside_window(t_pixel_pos pixel)
{
	return (pixel.x < 0 || pixel.x > WINDOW_WIDTH
		|| pixel.x < 0 || pixel.x > WINDOW_WIDTH);
}

int	get_highest_color(t_node n1, t_node n2)
{
	if (n1.z >= n2.z)
		return (n2.color);
	return (n1.color);
}

void	clear_frame(t_frame frame)
{
	char	*pixel;
	int		total;
	int		i;

	total = (WINDOW_WIDTH * WINDOW_HEIGHT);
	pixel = frame.addr;
	i = 0;
	while (i < total)
	{
		*(int *)pixel = 0;
		pixel += 4;
		i++;
	}
}

void	frame_draw_pixel(t_frame frame, t_pixel_pos p, int color)
{
	char	*pixel;

	if (p.x < 0 || p.y < 0 || p.x >= WINDOW_WIDTH || p.y >= WINDOW_HEIGHT)
		return ;
	pixel = frame.addr + (4) * (p.x + p.y * WINDOW_WIDTH);
	*(int *)pixel = color;
}
