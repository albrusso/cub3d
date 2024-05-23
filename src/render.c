/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:35:00 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/23 18:12:49 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double deg_to_rad(double degrees) {
    return degrees * (PI / 180.0);
}

static void	add_line_to_img(t_data *d, int i, int top, int bottom, t_img *t)
{
	int	color;

	color = t->data[5];
	for (int y = top; y < bottom; y++)
		d->i->data[y * WIN_X + i] = color;
}

t_img	*find_texture(t_data *d, t_raycast r, double angle)
{
	if (r.hit_vertical)
	{
		if (nor_angle(angle) > PI / 2 && nor_angle(angle) < 3 * PI / 2)
			return (d->ea);
		else
			return (d->we);
	}
	else
	{
		if (nor_angle(angle) > PI)
			return (d->so);
		else
			return (d->no);
	}
}

void	render(t_data *d)
{
	double	ray_angle;
	int		height;
	int		top;
	int		bottom;
	t_img	*t;
	int		i;
	t_raycast r;

	i = -1;
	ray_angle = d->p->dir - (d->p->fov / 2);
	while (++i < WIN_X)
	{
		r = raycasting(d, nor_angle(ray_angle));
		r.distance *= cos(nor_angle(ray_angle - d->p->dir));
		height = (int)((SIZE / r.distance) * ((WIN_X / 2) / tan(d->p->fov / 2)));
		top = (WIN_Y / 2) - (height / 2);
		bottom = (WIN_Y / 2) + (height / 2);
		if (top < 0)
			top = 0;
		if (bottom >= WIN_Y)
			bottom = WIN_Y;
		t = find_texture(d, r, ray_angle);
		add_line_to_img(d, i, top, bottom, t);
		ray_angle += d->p->fov / WIN_X;
	}
}
