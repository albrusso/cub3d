/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:35:00 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/22 18:32:00 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double deg_to_rad(double degrees) {
    return degrees * (PI / 180.0);
}

static void	add_line_to_img(t_data *d, int i, int top, int bottom, int color)
{
	for (int y = top; y < bottom; y++)
		d->i->data[y * WIN_X + i] = color;
}

void	render(t_data *d)
{
	double	fix_distance;
	double	ray_angle;
	int		height;
	int		top;
	int		bottom;
	int		color;
	int		i;
	t_raycast ray;

	i = -1;
	ray_angle = d->p->dir - (d->p->fov / 2);
	while (++i < WIN_X)
	{
		ray = raycasting(d, nor_angle(ray_angle));
		fix_distance = ray.distance * cos(nor_angle(ray_angle - d->p->dir));
		height = (int)((SIZE / fix_distance) * ((WIN_X / 2) / tan(d->p->fov / 2)));
		top = (WIN_Y / 2) - (height / 2);
		bottom = (WIN_Y / 2) + (height / 2);
		if (top < 0)
			top = 0;
		if (bottom >= WIN_Y)
			bottom = WIN_Y - 1;
		if (ray.hit_vertical)
			color = (0 << 16  | 255 << 8 | 0);
		else
				color = (0 << 16 | 0 << 8 | 255);
		add_line_to_img(d, i, top, bottom, color);
		ray_angle += d->p->fov / WIN_X;
	}
}
