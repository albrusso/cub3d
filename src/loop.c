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
	if (keypress == TURN_LEFT)
		d->p->dir -= SPIN_SPEED;
	if (keypress == TURN_RIGHT)
		d->p->dir += SPIN_SPEED;
}

 int	check_wall_up(t_player *player, char **map)
 {
 	int x2 = roundf(player->pos.x);
 	int y2 = roundf(player->pos.y);
 	if (map[(int)(y2 + 0.01)][(int)(x2 + 0.01 )] == '1')
 		return (0);
 	return (1);
 }

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

 void	check_move_u(t_player *player, t_data *d)
 {
 	double new_x = cos(player->dir) * 4;
	double new_y = sin(player->dir) * 4;

	double new_x2;
	double new_y2;
	int  map_grid_y;
	int  map_grid_x;
	//int  new_x2;
	//int  new_y2;
	new_x2 = roundf(player->pos.x + player->next.x); // get the new x position
	new_y2 = roundf(player->pos.y+ player->next.y); // get the new y position
	map_grid_x = (new_x2 / SIZE); // get the x position in the map
	map_grid_y = (new_y2 / SIZE); // get the y position in the map
	if (d->m->map[map_grid_y][map_grid_x] != '1' && \
	(d->m->map[map_grid_y][(int)d->p->pos.x / SIZE] != '1' && \
	d->m->map[(int)d->p->pos.y / SIZE][map_grid_x] != '1')) // check the wall hit and the diagonal wall hit
	{
		player->pos.x += new_x;
		player->pos.y += new_y;
	}
}

 void	check_move_d(t_player *player)
 {
 	double new_x = cos(player->dir) * 4;
	double new_y = sin(player->dir) * 4;
	//if (!has_collision)
	{
		player->pos.x -= new_x;
		player->pos.y -= new_y;

	}
 }

 void	check_move_r(t_player *player)
 {
	double new_x = cos(player->dir) * 4;
	double new_y = sin(player->dir) * 4;
	//if (!has_collision)
	{
		player->pos.x -= new_y;
		player->pos.y += new_x;

	}
 }

 void	check_move_l(t_player *player)
 {
 	double new_x = cos(player->dir) * 4;
	double new_y = sin(player->dir) * 4;
	//if (!has_collision)
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
		check_move_d(d->p);
	if (keypress == RIGHT)
		check_move_r(d->p);
	if (keypress == LEFT)
		check_move_l(d->p);
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