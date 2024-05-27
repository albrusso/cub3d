/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:11:56 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/27 09:14:01 by albrusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mylib/libft/libft.h"
# include "mylib/gnl/get_next_line.h"
# include "mylib/ft_printf/ft_printf.h"
# include "./minilibx-linux/mlx.h"

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
# define PLAYER_SPEED   6

# define ESC    65307
# define UP     119
# define DOWN   115
# define LEFT   97
# define RIGHT  100
# define TURN_RIGHT 65363
# define TURN_LEFT  65361
# define MAP_KEY    109

typedef struct s_raycast
{
	double	dist;
	double	ray_angle;
	double	h_inter_x;
	double	h_inter_y;
	double	v_inter_x;
	double	v_inter_y;
	int		x;
	bool	flag;
}	t_raycast;

typedef struct s_player
{
	double		x;
	double		y;
	double		fov;
	double		dir;
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
void	ok_map(t_data *d);
int		ok_line(t_data *d, t_map *m, char **a);
int		nsew(char c);
int		finish(t_map *m);
void	add_tex(t_map *m, char **a);
void	add_rgb(t_data *d, t_map *m, char **a);
void	skip_space(char *s, int *j);
void	map_dimension(t_map *m, char **map);
void	handle_error(t_data *d, char *s);
void	initialize(t_data *d, char *s);
void	arrfree(char **a);
int		cleanup(t_data *d);
void	map(t_data *d, t_map *m, char *s);
void	loop(t_data *d);
void	check_move(t_data *d, int keypress);
void	raycast(t_data *d);
void	render(t_data *d, int x);
float	norm_angle(float angle);
int		in_range(float angle, char c);
double	get_player_direction(char c);
void	get_info(t_data *d, int i, int j);
int		keypress(int code, void *_d);

#endif
