/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:11:56 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/25 18:06:42 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mylib/libft/libft.h"
# include "mylib/gnl/get_next_line.h"
# include "mylib/ft_printf/ft_printf.h"
# include "./minilibx/mlx.h"

# include <stdbool.h>
# include <math.h>
# include <stdint.h>

# define PI 3.141592999999999857863

# define RED    0x00FF0000
# define BLUE   0x000000FF
# define GREEN  0x0000FF00

# define WIN_X          1200
# define WIN_Y          800
# define SIZE   64
# define FOV           60
# define SPIN_SPEED     0.045
# define PLAYER_SPEED   0.1

# define ESC    53
# define UP     13
# define DOWN   1
# define LEFT   0
# define RIGHT  2
# define TURN_RIGHT 124
# define TURN_LEFT  123
# define MAP_KEY    109

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_raycast
{
	double	distance;
	double	ray_angle;
	double	horiz_x;
	double	horiz_y;
	double	vert_x;
	double	vert_y;
	int		index;
	bool	flag;
}	t_raycast;

typedef struct s_player
{
	t_point	pos;
	t_point	next;
	int		x;
	int		y;
	double	fov;
	double	dir;
}	t_player;

typedef struct s_map
{
	char	**map;
	int		map_x;
	int		map_y;
	char	dir;
	char	*no_tex;
	char	*so_tex;
	char	*we_tex;
	char	*ea_tex;
	int		frgb;
	int		crgb;
	int		max_x;
	int		max_y;
}	t_map;

typedef struct s_img
{
	void	*ptr;
	char	*file;
	int		*data;
	int		h;
	int		w;
	int		bits;
	int		len;
	int		endian;
}	t_img;

typedef struct s_face
{
	bool	up;
	bool	down;
	bool	right;
	bool	left;
}	t_face;

typedef struct s_cast
{
	t_point	step;
	t_point	next;
	t_point	intercept;
	t_point	hit_wall;
	double	distance;
	bool	find_wall;
}	t_cast;

typedef struct s_data
{
	t_map		*m;
	t_player	*p;
	t_raycast	*r;
	void		*mlx_ptr;
	void		*mlx_win;
	t_img		*no;
	t_img		*so;
	t_img		*we;
	t_img		*ea;
	t_img		*i;
}	t_data;

void	setup(t_data *d, int argc, char *argv[]);

void	handle_error(t_data *d, char *s);

void	initialize(t_data *d, char *s);

void	arrfree(char **a);
int		cleanup(t_data *d);

void	map(t_data *d, t_map *m, char *s);
void	loop(t_data *d);

t_raycast	raycast(t_data *d, double angle);



void	render(t_data *d);

float	nor_angle(float angle);

void	cast_rays(t_data *d);


#endif
