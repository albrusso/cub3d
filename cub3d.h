/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albrusso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:11:56 by albrusso          #+#    #+#             */
/*   Updated: 2024/05/21 17:27:34 by albrusso         ###   ########.fr       */
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

# define WIN_X          800
# define WIN_Y          600
# define TEXTURE_SIZE   32
# define FOV            60
# define SPIN_SPEED     0.045
# define PLAYER_SPEED   0.01

# define ESC    65307
# define UP     119
# define DOWN   115
# define LEFT   97
# define RIGHT  100
# define TURN_RIGHT 65363
# define TURN_LEFT  65361
# define MAP_KEY    109

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_raycast
{
	double distance;
	bool hit_vertical;
}	t_raycast;

typedef struct s_player
{
	int	x;
	int	y;
	double	angle;
	double	dir;
	float	fov;
	bool	spin;
	bool	lateral_move;
	bool	vertical_move;
}	t_player;

// typedef struct rgb
// {
// 	bool	complete;
// 	int		r;
// 	int		g;
// 	int		b;
// 	int		full_rgb;
// }	t_rgb;

// typedef struct s_image
// {
// 	void	*img;
// 	char	*add;
// 	int		*data;
// 	int		h;
// 	int		w;
// 	int		bits_per_pixel;
// 	int		size_len;
// 	int		endian;
// }	t_img;

// typedef struct s_texture
// {
// 	char	*no_tex;
// 	char	*so_tex;
// 	char	*we_tex;
// 	char	*ea_tex;
// 	char	**f_rgb;
// 	char	**c_rgb;
// }	t_texture;

// typedef struct s_mlx
// {
// 	void	*win;
// 	void	*ptr;
// }	t_mlx;

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

// void	cub3d_error(t_data *d, int err);
// void	handle_error(char *str, t_data *d);

// void	cleanup(t_data *d);

// void	t_data_init(t_data *d);

// int		map_reader(t_data *d, char *filename);
// int		map_copy(t_data *d, char *filename);

// int		get_texture(t_data *d);
// void	parse_map(t_data *d);

// void	set_spawn(char c, int x, int y, t_data *d);
// void	set_spawn2(char c, t_data *d);

// void	array_free(char **a);
// int		is_surrounded(char **map);

// void	ft_start_game(t_data *d);
// void	init_images(t_data *d);
// void	texture_init(t_data *d, char *path, t_img *texture);
// void	ft_init_window(t_data *d);
// int		keypress(int keypress, t_data *d);
// void	ft_angle(int keypress, t_data *d);

// void	check_move(t_data *d, int keypress);
// void	check_move_l(t_player *player, int keypress, char **map);
// void	check_move_r(t_player *player, int keypress, char **map);
// void	check_move_d(t_player *player, int keypress, char **map);
// void	check_move_u(t_player *player, int keypress, char **map);

// void	create_screen(t_data *d);
// void	draw_loop(t_data *d);
// void	background(t_data *d);
// void	reset_screen(t_data *d);
// int		convert_rgb(uint8_t red, uint8_t green, uint8_t blue);
// void	add_pixel(t_img *screen, int rgb, int x, int y);

// int		check_wall_up(t_player *player, char **map);
// int		check_wall_down(t_player *player, char **map);
// int		check_wall_right(t_player *player, char **map);
// int		check_wall_left(t_player *player, char **map);

// void	unload_imgs(t_data *d);
// void	ft_quit(t_data *d);

void	setup(t_data *d, int argc, char *argv[]);

void	handle_error(t_data *d, char *s);

void	initialize(t_data *d, char *s);

void	arrfree(char **a);
int		cleanup(t_data *d);

void	map(t_data *d, t_map *m, char *s);
void	loop(t_data *d);

t_raycast	raycasting(t_data *d, double angle);

void	render(t_data *d);


#endif
