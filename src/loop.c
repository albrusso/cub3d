/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:43:18 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/22 19:10:23 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	load_img(t_data *d, t_img *img, char *s)
{
	img->ptr = mlx_xpm_file_to_image(d->mlx_ptr, s, &img->w, &img->h);
	if (!img->ptr)
		handle_error(d, "Texture file not found");
	img->file = mlx_get_data_addr(img->ptr, &img->bits, &img->len, &img->endian);
	if (!img->file)
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
	render(d);
	mlx_put_image_to_window(d->mlx_ptr, d->mlx_win, d->i->ptr, 0, 0);
	return (0);
}

void	angle(int keypress, t_data *d)
{
	if (keypress == 123)
		d->p->dir -= SPIN_SPEED;
	if (keypress == 124)
		d->p->dir += SPIN_SPEED;
}

// int	check_wall_up(t_player *player, char **map)
// {
// 	double	safe;

// 	safe = 0.1;
// 	if (map[(int)(player->y + player->move_y * (0.1 + safe))]
// 		[(int)(player->x + player->move_x * (0.1 + safe))] == '1')
// 		return (0);
// 	return (1);
// }

// int	check_wall_down(t_player *player, char **map)
// {
// 	double	safe;

// 	safe = 0.1;
// 	if (map[(int)(player->y - player->move_y * (0.1 + safe))]
// 		[(int)(player->x - player->move_x * (0.1 + safe))] == '1')
// 		return (0);
// 	return (1);
// }

// int	check_wall_right(t_player *player, char **map)
// {
// 	double	safe;

// 	safe = 0.1;
// 	if (map[(int)(player->y + player->move_x * (0.1 + safe))]
// 		[(int)(player->x - player->move_y * (0.1 + safe))] == '1')
// 		return (0);
// 	return (1);
// }

// int	check_wall_left(t_player *player, char **map)
// {
// 	double	safe;

// 	safe = 0.1;
// 	if (map[(int)(player->y - player->move_x * (0.1 + safe))]
// 		[(int)(player->x + player->move_y * (0.1 + safe))] == '1')
// 		return (0);
// 	return (1);
// }

// void	check_move_u(t_player *player, int keypress, char **map)
// {
// 	if (keypress == UP && check_wall_up(player, map))
// 	{
// 		player->y += player->move_y * 0.1;
// 		player->x += player->move_x * 0.1;
// 	}
// }

// void	check_move_d(t_player *player, int keypress, char **map)
// {
// 	if (keypress == DOWN && check_wall_down(player, map))
// 	{
// 		player->y -= player->move_y * 0.1;
// 		player->x -= player->move_x * 0.1;
// 	}
// }

// void	check_move_r(t_player *player, int keypress, char **map)
// {
// 	if (keypress == RIGHT && check_wall_right(player, map))
// 	{
// 		player->y += player->move_y * 0.1;
// 		player->x -= player->move_x * 0.1;
// 	}
// }

// void	check_move_l(t_player *player, int keypress, char **map)
// {
// 	if (keypress == LEFT && check_wall_left(player, map))
// 	{
// 		player->move_x = sin(player->dir) * PLAYER_SPEED;
// 		player->move_y = -cos(player->dir) * PLAYER_SPEED;
// 	}
// }

// void	check_move(t_data *d, int keypress)
// {
	// check_move_u(d->p, keypress, d->m->map);
	// check_move_d(d->p, keypress, d->m->map);
	// check_move_r(d->p, keypress, d->m->map);
	// check_move_l(d->p, keypress, d->m->map);
// 	return ;
// }

int	keypress(int code, void *_d)
{
	t_data	*d;

	d = (t_data *)_d;
	if (code == ESC)
		cleanup(d);
	// if (code == UP || code == DOWN || \
	// 	code == LEFT || code == RIGHT)
	// 	check_move(d, code);
	if (code == 123 || code == 124)
		angle(code, d);
	return (0);
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
	mlx_hook(d->mlx_win, 2, 1L << 0, keypress, d);
	mlx_loop_hook(d->mlx_ptr, background, d);
	mlx_loop(d->mlx_ptr);
}