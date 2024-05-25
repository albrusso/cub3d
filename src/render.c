/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:35:00 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/25 18:00:52 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// t_img	*get_texture(t_data *d, t_raycast ray)
// {
// 	ray.ray_angle = nor_angle(ray.ray_angle);
// 	if (!ray.flag)
// 	{
// 		if (ray.ray_angle > M_PI / 2 && ray.ray_angle < 3 * (M_PI / 2))
// 			return (d->ea);
// 		else
// 			return (d->we);
// 	}
// 	else
// 	{
// 		if (ray.ray_angle > 0 && ray.ray_angle < M_PI)
// 			return (d->so);
// 		else
// 			return (d->no);
// 	}
// }

// void	add_pixel(t_data *d, int x, int y, int color)
// {
// 	if (x < 0)
// 		return ;
// 	else if (x >= WIN_X)
// 		return ;
// 	if (y < 0)
// 		return ;
// 	else if (y >= WIN_Y)
// 		return ;
// 	d->i->data[y * WIN_X + x] = color;
// }

// double	get_x_o(t_img	*texture, t_raycast ray)
// {
// 	double	x_o;

// 	if (ray.flag)
// 		x_o = (int)fmodf((ray.horiz_x * (texture->w / SIZE)), texture->w);
// 	else
// 		x_o = (int)fmodf((ray.vert_y * (texture->w / SIZE)), texture->w);
// 	return (x_o);
// }

// void	draw_vertical_line(t_data *d, t_raycast ray, double top, double bottom, double wall_h, int x)
// {
// 	double			x_o;
// 	double			y_o;
// 	t_img			*texture;
// 	uint32_t		*arr;
// 	double			factor;

// 	texture = get_texture(d, ray);
// 	arr = (uint32_t *)texture->data;
// 	factor = (double)texture->h / wall_h;
// 	x_o = get_x_o(texture, ray);
// 	y_o = (top - (WIN_Y / 2) + (wall_h / 2)) * factor;
// 	if (y_o < 0)
// 		y_o = 0;
// 	while (top < bottom)
// 	{
// 		add_pixel(d, x, top, arr[(int)y_o * texture->w + (int)x_o]);
// 		y_o += factor;
// 		top++;
// 	}
// }

// void	render(t_data *d)
// {
// 	int			x;
// 	double		angle;
// 	double		wall_h;
// 	double		top;
// 	double		bottom;
// 	t_raycast	ray;

// 	x = -1;
// 	angle = d->p->dir - (d->p->fov / 2);
// 	while (++x < WIN_X)
// 	{
// 		ray = raycast(d, angle);
// 		ray.distance *= cos(nor_angle(ray.ray_angle - d->p->dir));
// 		wall_h = (SIZE / ray.distance) * ((WIN_X / 2) / tan(d->p->fov / 2));
// 		bottom = (WIN_Y / 2) + (wall_h / 2);
// 		top = (WIN_Y / 2) - (wall_h / 2);
// 		if (bottom > WIN_Y)
// 			bottom = WIN_Y;
// 		if (top < 0)
// 			top = 0;
// 		draw_vertical_line(d, ray, top, bottom, wall_h, x);
// 		angle += (d->p->fov / WIN_X);
// 	}
	
// }
