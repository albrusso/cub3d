/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:18:27 by mgiovana          #+#    #+#             */
/*   Updated: 2024/05/27 11:18:29 by mgiovana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	nsew(char c)
{
	if (c == 'N' || c == 'S'
		|| c == 'E' || c == 'W')
		return (1);
	return (0);
}

void	get_info(t_data *d, int i, int j)
{
	d->m->map_x = j;
	d->m->map_y = i;
	d->p->dir = get_player_direction(d->m->map[i][j]);
}

int	finish(t_map *m)
{
	if (!m->no_tex || !m->so_tex
		|| !m->we_tex || !m->ea_tex
		|| !m->frgb || ! m->crgb)
		return (0);
	return (1);
}

void	skip_space(char *s, int *j)
{
	while (s[*j] && s[*j] == ' ')
		*j += 1;
}

void	map_dimension(t_map *m, char **map)
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
