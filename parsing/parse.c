/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lopayet- <lopayet-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:39:08 by lopayet-          #+#    #+#             */
/*   Updated: 2023/02/23 14:00:21 by lopayet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_line_length(char *line)
{
	char	**split;
	int		len;

	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	len = 0;
	while (split[len])
	{
		if (split[len][0] == '\n')
			break ;
		len++;
	}
	ft_free_split(split);
	return (len);
}

static int	get_fdf_map_dimensions(t_fdf *fdf, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	if (line == 0)
		return (close(fd), 1);
	fdf->map_w = get_line_length(line);
	free(line);
	if (fdf->map_w == -1)
		return (close(fd), 1);
	fdf->map_h = 1;
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		fdf->map_h++;
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

static void	free_err_map(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (fdf->map[i])
	{
		free(fdf->map[i]);
		i++;
	}
	free(fdf->map);
}

t_node	*get_fdf_map_line(t_fdf *fdf, char *line)
{
	char	**line_split;
	char	**point_split;
	t_node	*map_line;
	int		i;

	map_line = malloc(sizeof(t_node) * fdf->map_w);
	if (map_line == 0)
		return (NULL);
	line_split = ft_split(line, ' ');
	if (!line_split)
		return (free(map_line), NULL);
	i = -1;
	while (++i < fdf->map_w)
	{
		point_split = ft_split(line_split[i], ',');
		if (!point_split)
			return (ft_free_split(line_split), free(map_line), NULL);
		map_line[i].z = ft_atoi(point_split[0]);
		map_line[i].color = 0x888888;
		if (point_split[1])
			map_line[i].color = ft_atoi_hex(point_split[1] + 2);
		ft_free_split(point_split);
	}
	ft_free_split(line_split);
	return (map_line);
}

int	get_fdf_map(t_fdf *fdf, char *filename)
{
	int		fd;
	char	*line;
	int		i;

	if (get_fdf_map_dimensions(fdf, filename) != 0)
		return (1);
	fdf->map = malloc(sizeof(int *) * fdf->map_h);
	if (fdf->map == 0)
		return (1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (1);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		fdf->map[i] = get_fdf_map_line(fdf, line);
		free(line);
		if (!fdf->map[i])
			return (free_err_map(fdf), 1);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (0);
}
