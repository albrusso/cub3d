/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:15:21 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/21 14:08:30 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	finish(t_map *m)
{
	if (!m->no_tex || !m->so_tex
		|| !m->we_tex || !m->ea_tex
		|| !m->frgb || ! m->crgb)
		return (0);
	return (1);
}

static void	add_tex(t_map *m, char **a)
{
	char	*s;
	
	s = ft_strtrim(a[1], "\n");
	if (!ft_strncmp("NO", a[0], 2))
		m->no_tex = ft_strdup(s);
	else if (!ft_strncmp("SO", a[0], 2))
		m->so_tex = ft_strdup(s);
	else if (!ft_strncmp("WE", a[0], 2))
		m->we_tex = ft_strdup(s);
	else
		m->ea_tex = ft_strdup(s);
	free(s);
}

static void	add_rgb(t_map *m, char **a)
{
	char	**tmp;

	tmp = ft_split(a[1], ',');
	if (!ft_strncmp("F", a[0], 1))
		m->frgb = (ft_atoi(tmp[0]) << 16 | ft_atoi(tmp[1]) << 8 | ft_atoi(tmp[2]));
	else if (!ft_strncmp("C", a[0], 1))
		m->crgb = (ft_atoi(tmp[0]) << 16 | ft_atoi(tmp[1]) << 8 | ft_atoi(tmp[2]));
	arrfree(tmp);
}

int	ok_line(t_map *m, char **a)
{
	if (!ft_strncmp("NO", a[0], 2) || !ft_strncmp("SO", a[0], 2)
		|| !ft_strncmp("WE", a[0], 2) || !ft_strncmp("EA", a[0], 2))
		return (add_tex(m, a), 1);
	else if (!ft_strncmp("F", a[0], 1) || !ft_strncmp("C", a[0], 1))
		return (add_rgb(m, a), 1);
	else
		return (0);
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
			if (!ok_line(m, tmp))
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

static void	is_close(t_data *d)
{
	int	i;
	int	j;

	i = -1;
	while (d->m->map[++i])
	{
		j = -1;
		while (d->m->map[i][++j])
		{
			if (d->m->map[i][j] == '0')
			{
				if (!d->m->map[i][j + 1] || d->m->map[i][j + 1] == ' ')
					handle_error(d, "Map must be closed");
				if (!d->m->map[i][j - 1] || d->m->map[i][j - 1] == ' ')
					handle_error(d, "Map must be closed");
				if (!d->m->map[i + 1][j] || d->m->map[i + 1][j] == ' ')
					handle_error(d, "Map must be closed");
				if (!d->m->map[i - 1][j] || d->m->map[i - 1][j] == ' ')
					handle_error(d, "Map must be closed");
			}
		}
	}
}

int	nseo(char c)
{
	if (c == 'N' || c == 'S'
		|| c == 'O' || c == 'E')
		return (1);
	return (0);
}

void	get_info(t_data *d, int i, int j)
{
	d->m->map_x = j;
	d->m->map_y = i;
	d->m->dir = d->m->map[i][j];
}

static void	ok_map(t_data *d)
{
	int		i;
	int		j;
	bool	pos;

	i = -1;
	pos = false;
	while (d->m->map[++i])
	{
		j = -1;
		while (d->m->map[i][++j])
		{
			while (d->m->map[i][j] == ' ')
				j++;
			if (nseo(d->m->map[i][j]) && !pos)
			{
				pos = true;
				get_info(d, i, j);
			}
			else if (d->m->map[i][j] != '1' && d->m->map[i][j] != '0')
				handle_error(d, "Unexpected symbol in map");
			else if (nseo(d->m->map[i][j]) && pos)
				handle_error(d, "Multiple spawn in map");
		}
	}
	is_close(d);
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