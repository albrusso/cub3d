/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:21:56 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/21 17:29:59 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// int	intersection(double angle, float *h, float *step, bool flag)
// {
// 	if (!flag)
// 	{
// 		if (!(angle > PI / 2 && angle < 3 * PI / 2))
// 		{
// 			*h += TEXTURE_SIZE;
// 			return (-1);
// 		}
// 		*step *= -1;
// 	}
// 	else
// 	{
// 		if (angle > 0 && angle < PI)
// 		{
// 			*h += TEXTURE_SIZE;
// 			return (-1);
// 		}
// 		*step *= -1;
// 	}
// 	return (1);
// }

// double	find_x(t_data *d, double angle)
// {
// 	float	x;
// 	float	y;
// 	float	x_step;
// 	float	y_step;
// 	int		pixel;

// 	y_step = TEXTURE_SIZE;
// 	x_step = TEXTURE_SIZE / tan(angle);
// 	y = floor(d->p->y / TEXTURE_SIZE) * TEXTURE_SIZE;
// 	pixel = intersection(angle, &y, &y_step, true);
// 	x = d->p->x + (y - d->p->y) / tan(angle);
// 	if ((direct(angle, 'Y') && y_step < 0) || (!direct(angle, 'Y') && y_step > 0))
// 		y_step *= -1;
// 	while (wall(x, y - pixel, d))
// 	{
// 		x += x_step;
// 		y += y_step;
// 	}
// 	d->r->h.x = x;
// 	d->r->h.y = y;
// 	return (sqrt(pow(x - d->p->x, 2) + pow(y - d->p->y, 2)));
// }

// double	std_angle(double angle)
// {
// 	double 	tmp;

// 	if (angle < 0)
// 		tmp = angle + (2 * PI);
// 	if (tmp > (2 * PI))
// 		tmp = angle - (2 * PI);
// 	return (tmp);
// }

// double	find_y(t_data *d, double angle)
// {
// 	float	x;
// 	float	y;
// 	float	x_step;
// 	float	y_step;
// 	int		pixel;

// 	x_step = TEXTURE_SIZE;
// 	y_step = TEXTURE_SIZE * tan(angle);
// 	x = floor(d->p->x / TEXTURE_SIZE) * TEXTURE_SIZE;
// 	pixel = intersection(angle, &x, &x_step, false);
// 	if ((direct(angle, 'X') && y_step < 0) || (!direct(angle, 'X') && y_step > 0))
// 		y_step *= -1;
// 	while (wall(x - pixel, y, d))
// 	{
// 		x += x_step;
// 		y += y_step;
// 	}
// 	d->r->v.x = x;
// 	d->r->v.y = y;
// 	return (sqrt(pow(x - d->p->x, 2) + pow(y - d->p->y, 2)));
// }

// void	raycasting(t_data *d)
// {
// 	int		i;
// 	double	x;
// 	double	y;
// 	double	angle;

// 	d->r->angle = d->p->angle - (d->p->fov / 2);
// 	i = -1;
// 	while (++i < WIN_X)
// 	{
// 		angle = std_angle(d->r->angle);
// 		d->r->hit_wall = false;
// 		x = find_x(d, angle);
// 		y = find_y(d, angle);
// 	}
	
// }

double	range_angle(double angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

// static void	setup_ray(t_raycast *r, double angle)
// {
// 	r->down = angle > 0 && angle < PI;
// 	r->up = !r->down;
// 	r->right = angle < PI / 2 || angle > 1.5 * PI;
// 	r->left = !r->right;
// }

// bool	horizontal_intersection(t_data *d, t_raycast *r, double angle)
// {
// 	t_point	next;

// 	r->h.y = floor(d->p->y / TEXTURE_SIZE) * TEXTURE_SIZE;
// 	if (d->r->down)
// 		r->h.y += TEXTURE_SIZE;
// 	r->h.x = d->p->x + (r->h.y - d->p->y) / tan(angle);
// 	r->h_step.y = TEXTURE_SIZE;
// 	if (r->up)
// 		r->h_step.y *= -1;
// 	r->h_step.x = TEXTURE_SIZE / tan(angle);
// 	if (r->left && r->h_step.x > 0)
// 		r->h_step.x *= -1;
// 	if (r->right && r->h_step.x < 0)
// 		r->h_step.x *= -1;
// 	next = r->h;
// 	while (next.x >= 0 && next.x < WIN_X && next.y >= 0 && next.y < WIN_Y)
// 	{
// 		if (d->m->map[(int)(next.y / TEXTURE_SIZE) - r->up][(int)(next.x / TEXTURE_SIZE)] == '1')
// 		{
// 			r->h_wall = next;
// 			return (true);
// 		}
// 		else
// 		{
// 			next.x += r->h_step.x;
// 			next.y += r->h_step.y;
// 		}
// 	}
// 	return (false);
// }

// bool	vertical_intersection(t_data *d, t_raycast *r, double angle)
// {
// 	t_point	next;

// 	r->v.x = floor(d->p->x / TEXTURE_SIZE) * TEXTURE_SIZE;
// 	if (r->right)
// 		r->v.x += TEXTURE_SIZE;
// 	r->v.y = d->p->y + (r->v.x - d->p->x) * tan(angle);
// 	r->v_step.x = TEXTURE_SIZE;
// 	if (r->left)
// 		r->v_step.x *= -1;
// 	r->v_step.y = TEXTURE_SIZE * tan(angle);
// 	if (r->up && r->v_step.y > 0)
// 		r->v_step.y *= -1;
// 	if (r->down && r->v_step.y < 0)
// 		r->v_step.y *= -1;
// 	next = r->v;
// 	while (next.x >= 0 && next.x < WIN_X && next.y >= 0 && next.y < WIN_Y)
// 	{
// 		if (d->m->map[(int)(next.y / TEXTURE_SIZE)][(int)(next.x / TEXTURE_SIZE) - r->left] == '1')
// 		{
// 			r->v_wall = next;
// 			return (true);
// 		}
// 		else
// 		{
// 			next.x = r->v_step.x;
// 			next.y = r->v_step.y;
// 		}
// 	}
// 	return (false);
// }

t_raycast	raycasting(t_data *d, double angle)
{
	t_raycast ray;
	double ray_angle = range_angle(angle);
	bool is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
	bool is_ray_facing_up = !is_ray_facing_down;
	bool is_ray_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	bool is_ray_facing_left = !is_ray_facing_right;
	
	double xstep, ystep;
	t_point horz_intercept;
	bool found_horz_wall = false;
	t_point horz_wall_hit = {0, 0};

	horz_intercept.y = floor(d->p->y / TEXTURE_SIZE) * TEXTURE_SIZE;
    horz_intercept.y += is_ray_facing_down ? TEXTURE_SIZE : 0;
    horz_intercept.x = d->p->x + (horz_intercept.y - d->p->y) / tan(ray_angle);

	ystep = TEXTURE_SIZE;
	ystep *= is_ray_facing_up ? -1 : 1;

	xstep = TEXTURE_SIZE / tan(ray_angle);
	xstep *= (is_ray_facing_left && xstep > 0) ? -1 : 1;
	xstep *= (is_ray_facing_right && xstep < 0) ? -1 : 1;

	t_point next_horz_touch = horz_intercept;
	while (next_horz_touch.x >= 0 && next_horz_touch.x < WIN_X &&
			next_horz_touch.y >= 0 && next_horz_touch.y < WIN_Y) {
		if (d->m->map[(int)(next_horz_touch.y / TEXTURE_SIZE) - is_ray_facing_up]
					[(int)(next_horz_touch.x / TEXTURE_SIZE)] == '1') {
			found_horz_wall = true;
			horz_wall_hit = next_horz_touch;
			break;
		} else {
			next_horz_touch.x += xstep;
			next_horz_touch.y += ystep;
		}
	}
	
	t_point vert_intercept, vert_step;
	bool found_vert_wall = false;
	t_point vert_wall_hit = {0, 0};

	vert_intercept.x = floor(d->p->x / TEXTURE_SIZE) * TEXTURE_SIZE;
	vert_intercept.x += is_ray_facing_right ? TEXTURE_SIZE : 0;
	vert_intercept.y = d->p->y + (vert_intercept.x - d->p->x) * tan(ray_angle);

	vert_step.x = TEXTURE_SIZE;
	vert_step.x *= is_ray_facing_left ? -1 : 1;

	vert_step.y = TEXTURE_SIZE * tan(ray_angle);
	vert_step.y *= (is_ray_facing_up && vert_step.y > 0) ? -1 : 1;
	vert_step.y *= (is_ray_facing_down && vert_step.y < 0) ? -1 : 1;
	
	t_point next_vert_touch = vert_intercept;
	while (next_vert_touch.x >= 0 && next_vert_touch.x < WIN_X &&
		next_vert_touch.y >= 0 && next_vert_touch.y < WIN_Y) {
		if (d->m->map[(int)(next_vert_touch.y / TEXTURE_SIZE)]
				[(int)(next_vert_touch.x / TEXTURE_SIZE) - is_ray_facing_left] == '1') {
			found_vert_wall = true;
			vert_wall_hit = next_vert_touch;
			break;
		} else {
			next_vert_touch.x += vert_step.x;
			next_vert_touch.y += vert_step.y;
		}
	}
	
	double horz_hit_distance = found_horz_wall
	? sqrt((horz_wall_hit.x - d->p->x) * (horz_wall_hit.x - d->p->x) +
			(horz_wall_hit.y - d->p->y) * (horz_wall_hit.y - d->p->y))
	: INFINITY;

double vert_hit_distance = found_vert_wall
	? sqrt((vert_wall_hit.x - d->p->x) * (vert_wall_hit.x - d->p->x) +
			(vert_wall_hit.y - d->p->y) * (vert_wall_hit.y - d->p->y))
	: INFINITY;

	if (vert_hit_distance < horz_hit_distance) {
		ray.distance = vert_hit_distance;
		ray.hit_vertical = true;
	} else {
		ray.distance = horz_hit_distance;
		ray.hit_vertical = false;
	}
	return (ray);
}