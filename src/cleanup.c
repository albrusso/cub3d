/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:54:26 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/27 09:00:15 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	free_map(t_data *d)
{
	if (d->m->map)
		arrfree(d->m->map);
	if (d->m->no_tex)
		free(d->m->no_tex);
	if (d->m->so_tex)
		free(d->m->so_tex);
	if (d->m->we_tex)
		free(d->m->we_tex);
	if (d->m->ea_tex)
		free(d->m->ea_tex);
	free(d->m);
	d->m = NULL;
}

static void	free_player(t_data *d)
{
	if (d->p)
		free(d->p);
	d->p = NULL;
}

static void	free_raycast(t_data *d)
{
	free(d->r);
	d->r = NULL;
}

static void	free_img(t_data *d, t_img	*i)
{
	if (i->ptr)
		mlx_destroy_image(d->mlx_ptr, i->ptr);
	free(i);
	i = NULL;
}

int	cleanup(t_data *d)
{
	if (d->m)
		free_map(d);
	if (d->p)
		free_player(d);
	if (d->r)
		free_raycast(d);
	if (d->no)
		free_img(d, d->no);
	if (d->so)
		free_img(d, d->so);
	if (d->we)
		free_img(d, d->we);
	if (d->ea)
		free_img(d, d->ea);
	if (d->i)
		free_img(d, d->i);
	if (d->mlx_win)
		mlx_destroy_window(d->mlx_ptr, d->mlx_win);
	if (d->mlx_ptr)
		mlx_destroy_display(d->mlx_ptr);
	free(d->mlx_ptr);
	free(d);
	exit(EXIT_SUCCESS);
	return (1);
}
