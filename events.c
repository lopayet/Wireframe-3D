/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 12:32:26 by lopayet-          #+#    #+#             */
/*   Updated: 2023/02/10 14:38:49 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_keydown(int keysym, t_fdf *fdf)
{
	if (keysym == XK_Escape)
		fdf->exit = 1;
	return (0);
}

int	handle_window_kill(t_fdf *fdf)
{
	fdf->exit = 1;
	return (0);
}

int	handle_mousedown(int button, int x, int y, t_fdf *fdf)
{
	if (button == 1)
	{
		fdf->translate = 1;
		fdf->translate_x = x;
		fdf->translate_y = y;
	}
	if (button == 4 || button == 5)
	{
		if (button == 4)
			fdf->zoom = fdf->zoom * 1.1 + 1;
		else
			fdf->zoom = fdf->zoom * 0.9 - 1;
		if (fdf->zoom <= 0.5)
			fdf->zoom = 0.5;
		if (fdf->zoom >= 200.0)
			fdf->zoom = 200.0;
		display_map(*fdf);
	}
	return (0);
}

int	handle_mouseup(int button, int x, int y, t_fdf *fdf)
{
	if (button == 1)
	{
		fdf->translate = 0;
		fdf->translate_x = x;
		fdf->translate_y = y;
		display_map(*fdf);
	}
	return (0);
}

int	handle_mouse_move(int x, int y, t_fdf *fdf)
{
	int	x_diff;
	int	y_diff;

	if (fdf->translate)
	{
		x_diff = x - fdf->translate_x;
		y_diff = y - fdf->translate_y;
		fdf->offset_x += x_diff * 0.6;
		fdf->offset_y -= x_diff * 0.6;
		fdf->offset_x += y_diff * 0.6;
		fdf->offset_y += y_diff * 0.6;
		fdf->translate_x = x;
		fdf->translate_y = y;
	}
	return (0);
}
