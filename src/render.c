/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:35:00 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/21 17:29:19 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double deg_to_rad(double degrees) {
    return degrees * (PI / 180.0);
}

static void	add_line_to_img(t_data *d, int i, int top, int bottom, int color)
{
	for (int y = top; y < bottom; y++)
		mlx_pixel_put(d->mlx_ptr, d->mlx_win, i, y, color);
}

void	render(t_data *d)
{
	double	dist_plane;
	double	fix_distance;
	double	ray_angle;
	int		height;
	int		top;
	int		bottom;
	int		color;
	int		i;
	t_raycast ray;

	dist_plane = (WIN_X / 2) / tan(deg_to_rad(FOV / 2));
	i = -1;
	while (++i < WIN_X)
	{
		ray_angle = d->p->dir - deg_to_rad(FOV / 2) + (deg_to_rad(FOV) / WIN_X) * i;
		ray = raycasting(d, ray_angle);
		fix_distance = ray.distance * cos(ray_angle - d->p->dir);
		height = (int)(TEXTURE_SIZE / fix_distance * dist_plane);
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
	}
}