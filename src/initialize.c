/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:53:00 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/27 09:13:39 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	initialize_player(t_data *d)
{
	d->p->x = d->m->map_x * SIZE + SIZE / 2;
	d->p->y = d->m->map_y * SIZE + SIZE / 2;
	d->p->fov = (FOV * PI) / 180;
}

static void	initialize_map(t_data *d, char *s)
{
	d->m = ft_calloc(1, sizeof(t_map));
	d->m->no_tex = NULL;
	d->m->so_tex = NULL;
	d->m->we_tex = NULL;
	d->m->ea_tex = NULL;
	d->m->frgb = 0;
	d->m->crgb = 0;
	map(d, d->m, s);
}

void	initialize(t_data *d, char *s)
{
	d->mlx_ptr = NULL;
	d->mlx_win = NULL;
	d->p = ft_calloc(1, sizeof(t_player));
	d->r = ft_calloc(1, sizeof(t_raycast));
	d->no = ft_calloc(1, sizeof(t_img));
	d->so = ft_calloc(1, sizeof(t_img));
	d->we = ft_calloc(1, sizeof(t_img));
	d->ea = ft_calloc(1, sizeof(t_img));
	d->i = ft_calloc(1, sizeof(t_img));
	initialize_map(d, s);
	initialize_player(d);
}
