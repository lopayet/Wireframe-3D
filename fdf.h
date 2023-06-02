/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:55:19 by lopayet-          #+#    #+#             */
/*   Updated: 2023/06/02 18:46:14 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define WINDOW_WIDTH 2400
# define WINDOW_HEIGHT 1400
# define HEIGHT_MODIFIER 2.0

typedef struct s_pos		t_pos;
struct s_pos {
	int	x;
	int	y;
	int	z;
};

typedef struct s_pixel_pos	t_pixel_pos;
struct s_pixel_pos {
	int	x;
	int	y;
};

typedef struct s_frame		t_frame;
struct s_frame {
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
};

typedef struct s_node		t_node;
struct s_node {
	int	z;
	int	color;
};

typedef struct s_fdf		t_fdf;
struct s_fdf
{
	void	*mlx;
	void	*window;
	t_frame	frame;
	t_node	**map;
	int		map_w;
	int		map_h;
	double	angle;
	float	offset_x;
	float	offset_y;
	float	offset_z;
	float	zoom;
	int		exit;
	int		translate;
	int		translate_x;
	int		translate_y;
};

// fdf.c
void	fdf_set_defaults(t_fdf *fdf);
int		fdf_init_mlx(t_fdf *fdf);
void	fdf_free_map(t_fdf fdf);
void	fdf_destroy_mlx(t_fdf fdf);
int		fdf_loop(t_fdf *fdf);
// render/display.c
void	display_map(t_fdf fdf);
// render/utils.c
void	frame_draw_pixel(t_frame frame, t_pixel_pos p, int color);
void	clear_frame(t_frame frame);
int		ft_abs(int n);
int		is_pixel_outside_window(t_pixel_pos pixel);
int		get_highest_color(t_node n1, t_node n2);
// render/draw_line.c
void	frame_draw_line(t_frame frame,
			t_pixel_pos p1, t_pixel_pos p2, int color);
// parse.c
int		get_fdf_map(t_fdf *fdf, char *filename);
// events.c
int		handle_keydown(int keysym, t_fdf *fdf);
int		handle_window_kill(t_fdf *fdf);
int		handle_mousedown(int button, int x, int y, t_fdf *fdf);
int		handle_mouseup(int button, int x, int y, t_fdf *fdf);
int		handle_mouse_move(int x, int y, t_fdf *fdf);
// parsing
char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
void	*ft_free_split(char **split);
int		ft_atoi(const char *str);
int		ft_atoi_hex(char *str);

#endif
