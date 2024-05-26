/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:21:56 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/26 13:00:27 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1);
	}
	return (0);
}

int	inter_check(float angle, float *inter, float *step, int is_horizon)
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
		{
			*inter += SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	wall_hit(float x, float y, t_data *d)
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / SIZE);
	y_m = floor (y / SIZE);
	if ((y_m >= d->m->max_y || x_m >= d->m->max_x))
		return (0);
	if (d->m->map[y_m] && x_m <= (int)ft_strlen(d->m->map[y_m]))
		if (d->m->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

float	get_h_inter(t_data *d, float angl)
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = SIZE;
	x_step = SIZE / tan(angl);
	h_y = floor(d->p->pos.y / SIZE) * SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = d->p->pos.x + (h_y - d->p->pos.y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || \
		(!unit_circle(angl, 'y') && x_step < 0))
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, d))
	{
		h_x += x_step;
		h_y += y_step;
	}
	d->r->horiz_x = h_x;
	d->r->horiz_y = h_y;
	return (sqrt(pow(h_x - d->p->pos.x, 2) + \
	pow(h_y - d->p->pos.y, 2)));
}

float	get_v_inter(t_data *d, float angl)
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = SIZE;
	y_step = SIZE * tan(angl);
	v_x = floor(d->p->pos.x / SIZE) * SIZE;
	pixel = inter_check(angl, &v_x, &x_step, 0);
	v_y = d->p->pos.y + (v_x - d->p->pos.x) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0) || \
	(!unit_circle(angl, 'x') && y_step > 0))
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, d))
	{
		v_x += x_step;
		v_y += y_step;
	}
	d->r->vert_x = v_x;
	d->r->vert_y = v_y;
	return (sqrt(pow(v_x - d->p->pos.x, 2) + \
	pow(v_y - d->p->pos.y, 2)));
}

t_img	*get_texture(t_data *d, int flag)
{
	d->r->ray_angle = nor_angle(d->r->ray_angle);
	if (flag == 0)
	{
		if (d->r->ray_angle > M_PI / 2 && d->r->ray_angle < 3 * (M_PI / 2))
			return (d->ea);
		else
			return (d->we);
	}
	else
	{
		if (d->r->ray_angle > 0 && d->r->ray_angle < M_PI)
			return (d->so);
		else
			return (d->no);
	}
}

double	get_x_o(t_img	*texture, t_data *d)
{
	double	x_o;

	if (d->r->flag == 1)
		x_o = (int)fmodf((d->r->horiz_x * \
		(texture->w / SIZE)), texture->w);
	else
		x_o = (int)fmodf((d->r->vert_y * \
		(texture->w / SIZE)), texture->w);
	return (x_o);
}

void	add_pixel(t_data *d, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= WIN_X)
		return ;
	if (y < 0)
		return ;
	else if (y >= WIN_Y)
		return ;
	d->i->data[y * WIN_X + d->r->index] = color;
}

void	draw_wall(t_data *d, int t_pix, int b_pix, double wall_h)
{
	double			x_o;
	double			y_o;
	t_img			*texture;
	double			factor;

	texture = get_texture(d, d->r->flag);
	factor = (double)texture->h / wall_h;
	x_o = get_x_o(texture, d);
	y_o = (t_pix - (WIN_Y / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		add_pixel(d, d->r->index, t_pix, texture->data[(int)y_o * texture->w + (int)x_o]);
		y_o += factor;
		t_pix++;
	}
}

void	render_wall(t_data *d, int x)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	d->r->distance *= cos(nor_angle(d->r->ray_angle - d->p->dir));
	wall_h = (SIZE / d->r->distance) * ((WIN_X / 2) / \
	tan(d->p->fov / 2));
	b_pix = (WIN_Y / 2) + (wall_h / 2);
	t_pix = (WIN_Y / 2) - (wall_h / 2);
	if (b_pix > WIN_Y)
		b_pix = WIN_Y;
	if (t_pix < 0)
		t_pix = 0;
	d->r->index = x;
	draw_wall(d, t_pix, b_pix, wall_h);
}

void	cast_rays(t_data *d)
{
	double	h_inter;
	double	v_inter;
	int		x;

	x = 0;
	d->r->ray_angle = d->p->dir - (d->p->fov / 2);
	while (x < WIN_X)
	{
		d->r->flag = 0;
		h_inter = get_h_inter(d, nor_angle(d->r->ray_angle));
		v_inter = get_v_inter(d, nor_angle(d->r->ray_angle));
		if (v_inter <= h_inter)
			d->r->distance = v_inter;
		else
		{
			d->r->distance = h_inter;
			d->r->flag = 1;
		}
		render_wall(d, x);
		x++;
		d->r->ray_angle += (d->p->fov / WIN_X);
	}
}
