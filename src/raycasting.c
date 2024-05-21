/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:21:56 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/21 14:57:23 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	intersection(double angle, float *h, float *step, bool flag)
{
	if (!flag)
	{
		if (!(angle > PI / 2 && angle < 3 * PI / 2))
		{
			*h += TEXTURE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (angle > 0 && angle < PI)
		{
			*h += TEXTURE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

double	find_x(t_data *d, double angle)
{
	float	x;
	float	y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TEXTURE_SIZE;
	x_step = TEXTURE_SIZE / tan(angle);
	y = floor(d->p->y / TEXTURE_SIZE) * TEXTURE_SIZE;
	pixel = intersection(angle, &y, &y_step, true);
	x = d->p->x + (y - d->p->y) / tan(angle);
	if ((direct(angle, 'Y') && y_step < 0) || (!direct(angle, 'Y') && y_step > 0))
		y_step *= -1;
	while (wall(x, y - pixel, d))
	{
		x += x_step;
		y += y_step;
	}
	d->r->h.x = x;
	d->r->h.y = y;
	return (sqrt(pow(x - d->p->x, 2) + pow(y - d->p->y, 2)));
}

double	std_angle(double angle)
{
	double 	tmp;

	if (angle < 0)
		tmp = angle + (2 * PI);
	if (tmp > (2 * PI))
		tmp = angle - (2 * PI);
	return (tmp);
}

double	find_y(t_data *d, double angle)
{
	float	x;
	float	y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TEXTURE_SIZE;
	y_step = TEXTURE_SIZE * tan(angle);
	x = floor(d->p->x / TEXTURE_SIZE) * TEXTURE_SIZE;
	pixel = intersection(angle, &x, &x_step, false);
	if ((direct(angle, 'X') && y_step < 0) || (!direct(angle, 'X') && y_step > 0))
		y_step *= -1;
	while (wall(x - pixel, y, d))
	{
		x += x_step;
		y += y_step;
	}
	d->r->v.x = x;
	d->r->v.y = y;
	return (sqrt(pow(x - d->p->x, 2) + pow(y - d->p->y, 2)));
}

void	raycasting(t_data *d)
{
	int		i;
	double	x;
	double	y;
	double	angle;

	d->r->angle = d->p->angle - (d->p->fov / 2);
	i = -1;
	while (++i < WIN_X)
	{
		angle = std_angle(d->r->angle);
		d->r->hit_wall = false;
		x = find_x(d, angle);
		y = find_y(d, angle);
	}
	
}