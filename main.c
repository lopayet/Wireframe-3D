/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:43:31 by lopayet-          #+#    #+#             */
/*   Updated: 2023/02/23 13:30:46 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define PARSE_ERROR 1
#define MLX_ERROR 2

static void	set_hooks(t_fdf *fdf);

int	ft_putstr_fd(int fd, char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (write(fd, str, i));
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2 || get_fdf_map(&fdf, argv[1]) != 0)
	{
		ft_putstr_fd(1, "Error getting map.\n");
		return (PARSE_ERROR);
	}
	if (fdf_init_mlx(&fdf) != 0)
	{
		fdf_free_map(fdf);
		ft_putstr_fd(1, "MLX error.\n");
		return (MLX_ERROR);
	}
	fdf_set_defaults(&fdf);
	display_map(fdf);
	set_hooks(&fdf);
	mlx_loop(fdf.mlx);
	fdf_free_map(fdf);
	fdf_destroy_mlx(fdf);
	return (0);
}

static void	set_hooks(t_fdf *fdf)
{
	mlx_loop_hook(fdf->mlx, &fdf_loop, fdf);
	mlx_hook(fdf->window, KeyRelease, KeyReleaseMask, &handle_keydown, fdf);
	mlx_hook(fdf->window, DestroyNotify, NoEventMask, &handle_window_kill, fdf);
	mlx_hook(fdf->window, ButtonPress, ButtonPressMask, &handle_mousedown, fdf);
	mlx_hook(fdf->window, ButtonRelease, ButtonReleaseMask,
		&handle_mouseup, fdf);
	mlx_hook(fdf->window, MotionNotify, PointerMotionMask,
		&handle_mouse_move, fdf);
}
