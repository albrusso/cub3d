/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:14:59 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/27 09:16:14 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	ok_map(t_data *d)
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
			skip_space(d->m->map[i], &j);
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
