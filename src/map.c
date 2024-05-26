/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:15:21 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/27 00:46:14 by albrusso         ###   ########.fr       */
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

static void	map_dimension(t_map *m, char **map)
{
	int	i;
	int	curr;
	int	prev;
	int	len;

	i = 0;
	while (map[i])
		i++;
	m->max_y = i;
	i = 0;
	prev = (int)ft_strlen(map[i]);
	len = prev;
	while (map[++i])
	{
		curr = ft_strlen(m->map[i]);
		if (prev < curr)
			len = curr;
		prev = curr;
	}
	m->max_x = len;
}

static void	add_tex(t_map *m, char **a)
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

static void	add_rgb(t_data *d, t_map *m, char **a)
{
	char	**tmp;
	int		rgb[3];

	tmp = ft_split(a[1], ',');
	rgb[0] = ft_atoi(tmp[0]);
	rgb[1] = ft_atoi(tmp[1]);
	rgb[2] = ft_atoi(tmp[2]);
	if ((rgb[0] < 0 || rgb[0] > 255) || (rgb[1] < 0 || rgb[1] > 255) || (rgb[2] < 0 || rgb[2] > 255))
		handle_error(d, "rgb must be in range 0-255");
	if (!ft_strncmp("F", a[0], 1))
		m->frgb = (ft_atoi(tmp[0]) << 16 | ft_atoi(tmp[1]) << 8 | ft_atoi(tmp[2]));
	else if (!ft_strncmp("C", a[0], 1))
		m->crgb = (ft_atoi(tmp[0]) << 16 | ft_atoi(tmp[1]) << 8 | ft_atoi(tmp[2]));
	arrfree(tmp);
}

int	ok_line(t_data *d, t_map *m, char **a)
{
	if (!ft_strncmp("NO", a[0], 2) || !ft_strncmp("SO", a[0], 2)
		|| !ft_strncmp("WE", a[0], 2) || !ft_strncmp("EA", a[0], 2))
		return (add_tex(m, a), 1);
	else if (!ft_strncmp("F", a[0], 1) || !ft_strncmp("C", a[0], 1))
		return (add_rgb(d, m, a), 1);
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

static void	check_top_down(t_data *d, char *s, int i, int j)
{
	if (i == 0 || i == d->m->max_y - 1)
	{
		while (s[++j])
			if (s[j] != '1')
				handle_error(d, "Map must be closed");
	}
}

static void	check_left_right(t_data *d, char *s, int j)
{
	if (j == 0 || j == (int)ft_strlen(s))
		if (s[j] != '1')
			handle_error(d, "Map must be closed");
}

static void	skip_space(char *s, int *j)
{
	while (s[*j] && s[*j] == ' ')
		*j += 1;
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
			skip_space(d->m->map[i], &j);
			check_top_down(d, d->m->map[i], i, j);
			check_left_right(d, d->m->map[i], j);
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

int	nsew(char c)
{
	if (c == 'N' || c == 'S'
		|| c == 'E' || c == 'W')
		return (1);
	return (0);
}

double	get_player_direction(char c)
{
	if (c == 'N')
		return ((3 * PI / 2) + 0.005);
	if (c == 'S')
		return ((PI / 2) + 0.005);
	if (c == 'E')
		return (0 + 0.005);
	else
		return (PI + 0.005);
}

void	get_info(t_data *d, int i, int j)
{
	d->m->map_x = j;
	d->m->map_y = i;
	d->p->dir = get_player_direction(d->m->map[i][j]);
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
			if (nsew(d->m->map[i][j]) && !pos)
			{
				pos = true;
				get_info(d, i, j);
			}
			else if (nsew(d->m->map[i][j]) && pos)
				handle_error(d, "Multiple spawn in map");
			else if (d->m->map[i][j] != '1' && d->m->map[i][j] != '0')
				handle_error(d, "Unexpected symbol in map");
		}
	}
	map_dimension(d->m, d->m->map);
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