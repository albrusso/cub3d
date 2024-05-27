/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:21:56 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/27 09:11:16 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	inter_check(float angle, float *inter, float *step, char c)
{
	if (c == 'h')
	{
		if (angle > 0 && angle < PI)
		{
			*inter += SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > PI / 2 && angle < 3 * PI / 2))
		{
			*inter += SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	find_wall(float x, float y, t_data *d)
{
	int		map_x;
	int		map_y;

	if (x < 0 || y < 0)
		return (true);
	map_x = floor(x / SIZE);
	map_y = floor(y / SIZE);
	if ((map_y >= d->m->max_y || map_x >= d->m->max_x))
		return (true);
	if (d->m->map[map_y] && map_x <= (int)ft_strlen(d->m->map[map_y]))
		if (d->m->map[map_y][map_x] == '1')
			return (true);
	return (false);
}

float	get_h_inter(t_data *d, float angl)
{
	float	x;
	float	y;
	float	step_x;
	float	step_y;
	int		pixel;

	step_y = SIZE;
	step_x = SIZE / tan(angl);
	y = floor(d->p->y / SIZE) * SIZE;
	pixel = inter_check(angl, &y, &step_y, 'h');
	x = d->p->x + (y - d->p->y) / tan(angl);
	if ((in_range(angl, 'y') && step_x > 0) || \
		(!in_range(angl, 'y') && step_x < 0))
		step_x *= -1;
	while (!find_wall(x, y - pixel, d))
	{
		x += step_x;
		y += step_y;
	}
	d->r->h_inter_x = x;
	d->r->h_inter_y = y;
	return (sqrt(pow(x - d->p->x, 2) + pow(y - d->p->y, 2)));
}

float	get_v_inter(t_data *d, float angl)
{
	float	x;
	float	y;
	float	step_x;
	float	step_y;
	int		pixel;

	step_x = SIZE;
	step_y = SIZE * tan(angl);
	x = floor(d->p->x / SIZE) * SIZE;
	pixel = inter_check(angl, &x, &step_x, 'v');
	y = d->p->y + (x - d->p->x) * tan(angl);
	if ((in_range(angl, 'x') && step_y < 0) || \
	(!in_range(angl, 'x') && step_y > 0))
		step_y *= -1;
	while (!find_wall(x - pixel, y, d))
	{
		x += step_x;
		y += step_y;
	}
	d->r->v_inter_x = x;
	d->r->v_inter_y = y;
	return (sqrt(pow(x - d->p->x, 2) + pow(y - d->p->y, 2)));
}

void	raycast(t_data *d)
{
	double	h_inter;
	double	v_inter;
	int		x;

	x = 0;
	d->r->ray_angle = d->p->dir - (d->p->fov / 2);
	while (x < WIN_X)
	{
		d->r->flag = 0;
		h_inter = get_h_inter(d, norm_angle(d->r->ray_angle));
		v_inter = get_v_inter(d, norm_angle(d->r->ray_angle));
		if (v_inter <= h_inter)
			d->r->dist = v_inter;
		else
		{
			d->r->dist = h_inter;
			d->r->flag = true;
		}
		render(d, x);
		x++;
		d->r->ray_angle += (d->p->fov / WIN_X);
	}
}
