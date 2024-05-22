/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:21:56 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/22 18:17:07 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
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

double	range_angle(double angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

t_face	setup_face(double ray_angle)
{
	t_face	f;

	f.down = ray_angle > 0 && ray_angle < PI;
	f.up = !f.down;
	f.right = ray_angle < PI / 2 || ray_angle > 3 * PI / 2;
	f.left = !f.right;
	return (f);
}

t_cast	setup_horizontal_cast(t_data *d, t_face f, double ray_angle)
{
	t_cast	c;

	c.hit_wall.x = 0;
	c.hit_wall.y = 0;
	c.distance = INFINITY;
	c.find_wall = false;
	c.intercept.y = floor(d->p->pos.y / SIZE) * SIZE;
	if (f.down)
		c.intercept.y += SIZE;
	c.intercept.x = d->p->pos.x + (c.intercept.y - d->p->pos.y) / tan(ray_angle);
	c.step.y = SIZE;
	if (f.up)
		c.step.y *= -1;
	c.step.x = SIZE / tan(ray_angle);
	if ((f.left && c.step.x > 0) || (f.right && c.step.x < 0))
		c.step.x *= -1;
	return (c);
}

bool	wall_intercept(t_data *d, float x, float y)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = floor(x / SIZE);
	tmp_y = floor(y / SIZE);
	if (x < 0 || y < 0)
		return (false);
	if (tmp_y >= d->m->max_y || tmp_x >= d->m->max_x)
		return (false);
	if (d->m->map[tmp_y] && tmp_x < (int)ft_strlen(d->m->map[tmp_y]))
	{
		if (d->m->map[tmp_y][tmp_x] == '1')
			return (false);
	}
	return (true);
}

t_cast	horizontal_intercept(t_data *d, t_face f, double ray_angle)
{
	t_cast	c;

	c = setup_horizontal_cast(d, f, ray_angle);
	c.next = c.intercept;
	while (wall_intercept(d, c.next.x, c.next.y))
	{
		c.next.x += c.step.x;
		c.next.y += c.step.y;
	}
	c.hit_wall = c.next;
	c.find_wall = true;
	return (c);
}

t_cast	setup_vertical_cast(t_data *d, t_face f, double ray_angle)
{
	t_cast	c;

	c.hit_wall.x = 0;
	c.hit_wall.y = 0;
	c.distance = INFINITY;
	c.find_wall = false;
	c.intercept.x = floor(d->p->pos.x / SIZE) * SIZE;
	if (f.right)
		c.intercept.x += SIZE;
	c.intercept.y = d->p->pos.y + (c.intercept.x - d->p->pos.x) * tan(ray_angle);
	c.step.x = SIZE;
	if (f.left)
		c.step.x *= -1;
	c.step.y = SIZE * tan(ray_angle);
	if ((f.up && c.step.y > 0) || (f.down && c.step.y < 0))
		c.step.y *= -1;
	return (c);
}

t_cast	vertical_intercept(t_data *d, t_face f, double ray_angle)
{
	t_cast	c;

	c = setup_vertical_cast(d, f, ray_angle);
	c.next = c.intercept;
	while (wall_intercept(d, c.next.x, c.next.y))
	{
		c.next.x += c.step.x;
		c.next.y += c.step.y;
	}
	c.hit_wall = c.next;
	c.find_wall = true;
	return (c);
}

float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * PI);
	if (angle > (2 * PI))
		angle -= (2 * PI);
	return (angle);
}

t_raycast	raycasting(t_data *d, double ray_angle)
{
	t_raycast	ray;
	t_cast		h;
	t_cast		v;
	t_face		f;

	f = setup_face(ray_angle);
	h = horizontal_intercept(d, f, ray_angle);
	v = vertical_intercept(d, f, ray_angle);
	if (h.find_wall)
		h.distance = sqrt(pow(h.hit_wall.x - d->p->pos.x, 2) + pow(h.hit_wall.y - d->p->pos.y, 2));
	if (v.find_wall)
		v.distance = sqrt(pow(v.hit_wall.x - d->p->pos.x, 2) + pow(v.hit_wall.y - d->p->pos.y, 2));
	if (v.distance < h.distance)
	{
		ray.distance = v.distance;
		ray.hit_vertical = true;
	}
	else
	{
		ray.distance = h.distance;
		ray.hit_vertical = false;
	}
	return (ray);
}
