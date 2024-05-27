/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:43:18 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/27 09:13:08 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	load_img(t_data *d, t_img *img, char *s)
{
	img->ptr = mlx_xpm_file_to_image(d->mlx_ptr, s, &img->w, &img->h);
	if (!img->ptr)
		handle_error(d, "Texture file not found");
	img->data = (int *)mlx_get_data_addr(img->ptr, &img->bits,
			&img->len, &img->endian);
	if (!img->data)
		handle_error(d, "Failed mlx_get_data_addr()");
}

static void	angle(int keypress, t_data *d)
{
	if (keypress == TURN_LEFT)
		d->p->dir -= SPIN_SPEED;
	if (keypress == TURN_RIGHT)
		d->p->dir += SPIN_SPEED;
}

int	background(void *_d)
{
	t_data	*d;
	int		x;
	int		y;

	d = (t_data *)_d;
	y = -1;
	while (++y < WIN_Y)
	{
		x = -1;
		while (++x < WIN_X)
		{
			if (y >= WIN_Y / 2)
				d->i->data[y * WIN_X + x] = d->m->frgb;
			else if (y < WIN_Y / 2)
				d->i->data[y * WIN_X + x] = d->m->crgb;
		}
	}
	raycast(d);
	mlx_put_image_to_window(d->mlx_ptr, d->mlx_win, d->i->ptr, 0, 0);
	return (0);
}

int	keypress(int code, void *_d)
{
	t_data	*d;

	d = (t_data *)_d;
	if (code == ESC)
		cleanup(d);
	if (code == UP || code == DOWN
		|| code == LEFT || code == RIGHT)
		check_move(d, code);
	if (code == TURN_RIGHT || code == TURN_LEFT)
		angle(code, d);
	return (0);
}

void	loop(t_data *d)
{
	d->mlx_ptr = mlx_init();
	load_img(d, d->no, d->m->no_tex);
	load_img(d, d->so, d->m->so_tex);
	load_img(d, d->we, d->m->we_tex);
	load_img(d, d->ea, d->m->ea_tex);
	d->mlx_win = mlx_new_window(d->mlx_ptr, WIN_X, WIN_Y, "cub3d");
	d->i->ptr = mlx_new_image(d->mlx_ptr, WIN_X, WIN_Y);
	d->i->data = (int *)mlx_get_data_addr(d->i->ptr, &d->i->bits, \
		&d->i->len, &d->i->endian);
	mlx_hook(d->mlx_win, 17, 0, cleanup, d);
	mlx_hook(d->mlx_win, 2, 1L << 0, keypress, d);
	mlx_loop_hook(d->mlx_ptr, background, d);
	mlx_loop(d->mlx_ptr);
}
