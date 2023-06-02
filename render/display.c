/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:46:49 by lopayet-          #+#    #+#             */
/*   Updated: 2023/06/02 18:45:02 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_pixel_pos	get_projection(t_pos pos, double angle);
static void			frame_draw_3d_line(t_fdf fdf, t_pos p1, t_pos p2,
						int color);
static void			frame_draw_map_line(t_fdf fdf, int y);
static void			frame_draw_map_row(t_fdf fdf, int x);

void	display_map(t_fdf fdf)
{
	int	i;

	mlx_clear_window(fdf.mlx, fdf.window);
	clear_frame(fdf.frame);
	i = -1;
	while (++i < fdf.map_h)
		frame_draw_map_line(fdf, i);
	i = -1;
	while (++i < fdf.map_w)
		frame_draw_map_row(fdf, i);
	mlx_put_image_to_window(fdf.mlx, fdf.window, fdf.frame.mlx_img, 0, 0);
}

static t_pixel_pos	get_projection(t_pos pos, double angle)
{
	t_pixel_pos	res;

	res.x = (double)(pos.x - pos.y) *cos(angle) + 0.5;
	res.y = (double)(pos.x + pos.y) *sin(angle) - (double)pos.z * (1.0 / HEIGHT_MODIFIER) + 0.5;
	return (res);
}

static void	frame_draw_3d_line(t_fdf fdf, t_pos p1, t_pos p2, int color)
{
	t_pixel_pos	pixel_1;
	t_pixel_pos	pixel_2;

	p1.x *= fdf.zoom;
	p1.y *= fdf.zoom;
	p1.z *= fdf.zoom;
	p2.x *= fdf.zoom;
	p2.y *= fdf.zoom;
	p2.z *= fdf.zoom;
	p1.x += fdf.offset_x;
	p1.y += fdf.offset_y;
	p1.z += fdf.offset_z;
	p2.x += fdf.offset_x;
	p2.y += fdf.offset_y;
	p2.z += fdf.offset_z;
	pixel_1 = get_projection(p1, fdf.angle);
	pixel_2 = get_projection(p2, fdf.angle);
	if (is_pixel_outside_window(pixel_1)
		&& is_pixel_outside_window(pixel_2))
		return ;
	frame_draw_line(fdf.frame, pixel_1, pixel_2, color);
}

static void	frame_draw_map_line(t_fdf fdf, int y)
{
	t_pos	p1;
	t_pos	p2;
	int		x;
	int		color;

	x = 0;
	p1.y = y;
	p2.y = y;
	while (x < fdf.map_w - 1)
	{
		p1.x = x;
		p1.z = fdf.map[y][x].z;
		p2.x = x + 1;
		p2.z = fdf.map[y][x + 1].z;
		color = get_highest_color(fdf.map[y][x], fdf.map[y][x + 1]);
		frame_draw_3d_line(fdf, p1, p2, color);
		x++;
	}
}

static void	frame_draw_map_row(t_fdf fdf, int x)
{
	t_pos	p1;
	t_pos	p2;
	int		y;
	int		color;

	y = 0;
	p1.x = x;
	p2.x = x;
	while (y < fdf.map_h - 1)
	{
		p1.y = y;
		p1.z = fdf.map[y][x].z;
		p2.y = y + 1;
		p2.z = fdf.map[y + 1][x].z;
		color = get_highest_color(fdf.map[y][x], fdf.map[y + 1][x]);
		frame_draw_3d_line(fdf, p1, p2, color);
		y++;
	}
}
