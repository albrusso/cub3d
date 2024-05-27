/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:35:00 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/27 09:00:39 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_img	*find_texture(t_data *d, int flag)
{
	d->r->ray_angle = norm_angle(d->r->ray_angle);
	if (!flag)
	{
		if (d->r->ray_angle > PI / 2 && d->r->ray_angle < 3 * (PI / 2))
			return (d->ea);
		else
			return (d->we);
	}
	else
	{
		if (d->r->ray_angle > 0 && d->r->ray_angle < PI)
			return (d->so);
		else
			return (d->no);
	}
}

double	find_tex_x(t_img	*t, t_data *d)
{
	double	tex_x;

	if (d->r->flag == 1)
		tex_x = (int)fmodf((d->r->h_inter_x * (t->w / SIZE)), t->w);
	else
		tex_x = (int)fmodf((d->r->v_inter_y * (t->w / SIZE)), t->w);
	return (tex_x);
}

static void	add_pixel(t_data *d, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= WIN_X)
		return ;
	if (y < 0)
		return ;
	else if (y >= WIN_Y)
		return ;
	d->i->data[y * WIN_X + x] = color;
}

static void	draw_vert_line(t_data *d, int start, int end, double height)
{
	double		tex_x;
	double		tex_y;
	double		step_y;
	t_img		*t;

	t = find_texture(d, d->r->flag);
	step_y = (double)t->h / height;
	tex_x = find_tex_x(t, d);
	tex_y = (start - (WIN_Y / 2) + (height / 2)) * step_y;
	if (tex_y < 0)
		tex_y = 0;
	while (start < end)
	{
		add_pixel(d, d->r->x, start, t->data[(int)tex_y * t->w + (int)tex_x]);
		tex_y += step_y;
		start++;
	}
}

void	render(t_data *d, int x)
{
	double	height;
	double	end;
	double	start;

	d->r->dist *= cos(norm_angle(d->r->ray_angle - d->p->dir));
	height = (SIZE / d->r->dist) * ((WIN_X / 2) / \
	tan(d->p->fov / 2));
	end = (WIN_Y / 2) + (height / 2);
	start = (WIN_Y / 2) - (height / 2);
	if (end > WIN_Y)
		end = WIN_Y;
	if (start < 0)
		start = 0;
	d->r->x = x;
	draw_vert_line(d, start, end, height);
}
