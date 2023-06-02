/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 15:09:45 by lopayet-          #+#    #+#             */
/*   Updated: 2023/02/10 15:09:47 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_set_defaults(t_fdf *fdf)
{
	fdf->angle = 0.6;
	fdf->zoom = 40;
	fdf->offset_x = WINDOW_WIDTH / 3;
	fdf->offset_y = 0;
	fdf->offset_z = 0;
	fdf->translate = 0;
	fdf->exit = 0;
}

int	fdf_loop(t_fdf *fdf)
{
	if (fdf->exit)
		mlx_loop_end(fdf->mlx);
	return (0);
}

int	fdf_init_mlx(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (fdf->mlx == NULL)
		return (1);
	fdf->window = mlx_new_window(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "fdf");
	if (fdf->window == NULL)
		return (free(fdf->mlx), 1);
	fdf->frame.mlx_img = mlx_new_image(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (fdf->frame.mlx_img == NULL)
	{
		mlx_destroy_window(fdf->mlx, fdf->window);
		mlx_destroy_display(fdf->mlx);
		return (free(fdf->mlx), 1);
	}
	fdf->frame.addr = mlx_get_data_addr(fdf->frame.mlx_img,
			&(fdf->frame.bpp), &(fdf->frame.line_len), &(fdf->frame.endian));
	if (fdf->frame.addr == NULL)
	{
		mlx_destroy_window(fdf->mlx, fdf->window);
		mlx_destroy_image(fdf->mlx, fdf->frame.mlx_img);
		mlx_destroy_display(fdf->mlx);
		return (free(fdf->mlx), 1);
	}
	return (0);
}

void	fdf_destroy_mlx(t_fdf fdf)
{
	mlx_destroy_window(fdf.mlx, fdf.window);
	mlx_destroy_image(fdf.mlx, fdf.frame.mlx_img);
	mlx_destroy_display(fdf.mlx);
	free(fdf.mlx);
}

void	fdf_free_map(t_fdf fdf)
{
	int	i;

	i = 0;
	while (i < fdf.map_h)
	{
		free(fdf.map[i]);
		i++;
	}
	free(fdf.map);
}
