/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:15:21 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/27 09:16:01 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	add_tex(t_map *m, char **a)
{
	char	*s;

	s = ft_strtrim(a[1], "\n");
	if (!ft_strncmp("NO", a[0], 2))
		m->no_tex = ft_substr(a[1], 0, ft_strlen(a[1]) - 1);
	else if (!ft_strncmp("SO", a[0], 2))
		m->so_tex = ft_substr(a[1], 0, ft_strlen(a[1]) - 1);
	else if (!ft_strncmp("WE", a[0], 2))
		m->we_tex = ft_substr(a[1], 0, ft_strlen(a[1]) - 1);
	else
		m->ea_tex = ft_substr(a[1], 0, ft_strlen(a[1]) - 1);
	free(s);
}

void	add_rgb(t_data *d, t_map *m, char **a)
{
	char	**tmp;
	int		rgb[3];

	tmp = ft_split(a[1], ',');
	rgb[0] = ft_atoi(tmp[0]);
	rgb[1] = ft_atoi(tmp[1]);
	rgb[2] = ft_atoi(tmp[2]);
	if ((rgb[0] < 0 || rgb[0] > 255)
		|| (rgb[1] < 0 || rgb[1] > 255)
		|| (rgb[2] < 0 || rgb[2] > 255))
		handle_error(d, "rgb must be in range 0-255");
	if (!ft_strncmp("F", a[0], 1))
		m->frgb = (ft_atoi(tmp[0]) << 16
				| ft_atoi(tmp[1]) << 8 | ft_atoi(tmp[2]));
	else if (!ft_strncmp("C", a[0], 1))
		m->crgb = (ft_atoi(tmp[0]) << 16
				| ft_atoi(tmp[1]) << 8 | ft_atoi(tmp[2]));
	arrfree(tmp);
}

void	texture(t_data *d, t_map *m, int fd)
{
	char	*s;
	char	**tmp;

	s = get_next_line(fd);
	while (s && !finish(m))
	{
		if (!ft_strncmp(s, "\n", 1))
			free(s);
		else
		{
			tmp = ft_split(s, ' ');
			if (!ok_line(d, m, tmp))
			{
				free(s);
				arrfree(tmp);
				handle_error(d, "Bad texture info");
			}
			free(s);
			arrfree(tmp);
		}
		s = get_next_line(fd);
	}
	free(s);
	if (!finish(m))
		handle_error(d, "Missing same texture");
}

static void	map2d(t_data *d, t_map *m, int fd)
{
	char	*s;
	char	*buffer;

	s = get_next_line(fd);
	buffer = ft_calloc(1, 1);
	while (s && !ft_strncmp(s, "\n", 1))
	{
		free(s);
		s = get_next_line(fd);
	}
	if (!s)
		handle_error(d, "Missing map");
	while (s)
	{
		if (!ft_strncmp(s, "\n", 1))
			free(s);
		else
			buffer = ft_strjoin_gnl(buffer, s);
		s = get_next_line(fd);
	}
	m->map = ft_split(buffer, '\n');
	free(buffer);
}

void	map(t_data *d, t_map *m, char *s)
{
	int	fd;

	fd = open(s, O_RDONLY);
	if (fd < 0)
		handle_error(d, "Failed open()");
	texture(d, m, fd);
	map2d(d, m, fd);
	close(fd);
	ok_map(d);
}
