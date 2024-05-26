/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:43:18 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/27 00:10:05 by albrusso         ###   ########.fr       */
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

void	angle(int keypress, t_data *d)
{
	if (keypress == TURN_LEFT)
		d->p->dir -= SPIN_SPEED;
	if (keypress == TURN_RIGHT)
		d->p->dir += SPIN_SPEED;
}

void	check_move_u(t_player *player, t_data *d)
{
	double	new_x;
	double	new_y;
	int		map_grid_y;
	int		map_grid_x;

	new_x = cos(player->dir) * 4;
	new_y = sin(player->dir) * 4;
	map_grid_x = ((player->pos.x + new_x) / SIZE);
	map_grid_y = ((player->pos.y + new_y) / SIZE);
	if (d->m->map[map_grid_y][map_grid_x] != '1' && \
	(d->m->map[map_grid_y][(int)d->p->pos.x / SIZE] != '1' && \
		d->m->map[(int)d->p->pos.y / SIZE][map_grid_x] != '1'))
	{
		player->pos.x += new_x;
		player->pos.y += new_y;
	}
}

void	check_move_d(t_player *player, t_data *d)
{
	double	new_x;
	double	new_y;
	int		map_grid_y;
	int		map_grid_x;

	new_x = cos(player->dir) * 4;
	new_y = sin(player->dir) * 4;
	map_grid_x = ((player->pos.x - new_x) / SIZE);
	map_grid_y = ((player->pos.y - new_y) / SIZE);
	if (d->m->map[map_grid_y][map_grid_x] != '1' && \
	(d->m->map[map_grid_y][(int)d->p->pos.x / SIZE] != '1' && \
		d->m->map[(int)d->p->pos.y / SIZE][map_grid_x] != '1'))
	{
		player->pos.x -= new_x;
		player->pos.y -= new_y;
	}
}

void	check_move_r(t_player *player, t_data *d)
{
	double	new_x;
	double	new_y;
	int		map_grid_y;
	int		map_grid_x;

	new_x = cos(player->dir) * 4;
	new_y = sin(player->dir) * 4;
	map_grid_x = ((player->pos.x - new_y) / SIZE);
	map_grid_y = ((player->pos.y + new_x) / SIZE);
	if (d->m->map[map_grid_y][map_grid_x] != '1' && \
	(d->m->map[map_grid_y][(int)d->p->pos.x / SIZE] != '1' && \
		d->m->map[(int)d->p->pos.y / SIZE][map_grid_x] != '1'))
	{
		player->pos.x -= new_y;
		player->pos.y += new_x;
	}
}

void	check_move_l(t_player *player, t_data *d)
{
	double	new_x;
	double	new_y;
	int		map_grid_y;
	int		map_grid_x;

	new_x = cos(player->dir) * 4;
	new_y = sin(player->dir) * 4;
	map_grid_x = ((player->pos.x + new_y) / SIZE);
	map_grid_y = ((player->pos.y - new_x) / SIZE);
	if (d->m->map[map_grid_y][map_grid_x] != '1' && \
	(d->m->map[map_grid_y][(int)d->p->pos.x / SIZE]!= '1' && \
		d->m->map[(int)d->p->pos.y / SIZE][map_grid_x]!= '1'))
	{
		player->pos.x += new_y;
		player->pos.y -= new_x;
	}
}

void	check_move(t_data *d, int keypress)
{
	if (keypress == UP)
	 	check_move_u(d->p, d);
	if (keypress == DOWN)	 
		check_move_d(d->p, d);
	if (keypress == RIGHT)
		check_move_r(d->p, d);
	if (keypress == LEFT)
		check_move_l(d->p, d);
	return ;
}

int	keypress(int code, void *_d)
{
	t_data	*d;

	d = (t_data *)_d;
	if (code == ESC)
		cleanup(d);
	 if (code == UP || code == DOWN || \
	 	code == LEFT || code == RIGHT)
	 	check_move(d, code);
	if (code == TURN_RIGHT || code == TURN_LEFT)
		angle(code, d);
	return (0);
}

void	get_angle(t_data *d)
{
	char	c;

	c = d->m->map[d->m->map_y][d->m->map_x];
	if (c == 'N')
		d->p->dir = 3 * PI / 2;
	if (c == 'S')
		d->p->dir = PI / 2;
	if (c == 'E')
		d->p->dir = 0;
	if (c == 'W')
		d->p->dir = PI;
	d->p->pos.x = (d->m->map_x * SIZE) + SIZE / 2;
	d->p->pos.y = (d->m->map_y * SIZE) + SIZE / 2;
	d->p->fov = (FOV * PI / 180);
}

void	loop(t_data *d)
{
	d->mlx_ptr = mlx_init();
	d->mlx_win = mlx_new_window(d->mlx_ptr, WIN_X, WIN_Y, "cub3d");
	load_img(d, d->no, d->m->no_tex);
	load_img(d, d->so, d->m->so_tex);
	load_img(d, d->we, d->m->we_tex);
	load_img(d, d->ea, d->m->ea_tex);
	d->i->ptr = mlx_new_image(d->mlx_ptr, WIN_X, WIN_Y);
	d->i->data = (int *)mlx_get_data_addr(d->i->ptr, &d->i->bits, &d->i->len, &d->i->endian);
	get_angle(d);
	mlx_hook(d->mlx_win, 17, 0, cleanup, d);
	mlx_hook(d->mlx_win, 2, 1L << 0, keypress, d);
	mlx_loop_hook(d->mlx_ptr, background, d);
	mlx_loop(d->mlx_ptr);
}
