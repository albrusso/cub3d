/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 09:03:27 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/27 14:59:23 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_move_u(t_player *player, t_data *d)
{
	double	new_x;
	double	new_y;
	int		map_y;
	int		map_x;

	new_x = cos(player->dir) * PLAYER_SPEED;
	new_y = sin(player->dir) * PLAYER_SPEED;
	map_x = ((player->x + new_x) / SIZE);
	map_y = ((player->y + new_y) / SIZE);
	if (d->m->map[map_y][map_x] != '1')
	{
		player->x += new_x;
		player->y += new_y;
	}
}

static void	check_move_d(t_player *player, t_data *d)
{
	double	new_x;
	double	new_y;
	int		map_y;
	int		map_x;

	new_x = cos(player->dir) * PLAYER_SPEED;
	new_y = sin(player->dir) * PLAYER_SPEED;
	map_x = ((player->x - new_x) / SIZE);
	map_y = ((player->y - new_y) / SIZE);
	if (d->m->map[map_y][map_x] != '1')
	{
		player->x -= new_x;
		player->y -= new_y;
	}
}

static void	check_move_r(t_player *player, t_data *d)
{
	double	new_x;
	double	new_y;
	int		map_y;
	int		map_x;

	new_x = cos(player->dir) * PLAYER_SPEED;
	new_y = sin(player->dir) * PLAYER_SPEED;
	map_x = ((player->x - new_y) / SIZE);
	map_y = ((player->y + new_x) / SIZE);
	if (d->m->map[map_y][map_x] != '1')
	{
		player->x -= new_y;
		player->y += new_x;
	}
}

static void	check_move_l(t_player *player, t_data *d)
{
	double	new_x;
	double	new_y;
	int		map_y;
	int		map_x;

	new_x = cos(player->dir) * PLAYER_SPEED;
	new_y = sin(player->dir) * PLAYER_SPEED;
	map_x = ((player->x + new_y) / SIZE);
	map_y = ((player->y - new_x) / SIZE);
	if (d->m->map[map_y][map_x] != '1')
	{
		player->x += new_y;
		player->y -= new_x;
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
