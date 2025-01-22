/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:26:06 by noldiane          #+#    #+#             */
/*   Updated: 2025/01/18 15:56:30 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

/* LIBRARIES */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

# include "colors.h"
# include "errors.h"
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

/* DATA */

# define DEBUG 0

# define MOVE_SPEED 0.5;
# define ROTATE_SPEED 0.015

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720

# define FORWARD_KEY 122
# define BACK_KEY 115
# define LEFT_KEY 113
# define RIGHT_KEY 100

# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

# define PI 3.141592653589
# define RAD_TO_DEG = 180.0f / PI;

# define QUIT_KEY 97
# define ESC_KEY 65307
# define EXIT_BUTTON

/* STRUCTURES */

typedef struct t_rgb
{
	double r;
	double g;
	double b;
} t_rgb;

typedef	struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;

	int 	angle;

	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;

	bool	rotate_left;
	bool	rotate_right;

	bool	touching_wall;
} t_player;

typedef struct s_game
{
	int		map_height;

	char	**map;

	int		F_COLOR;
	int		C_COLOR;

	double		camera_x;
	double		camera_y;

	char	*NO_TEXTURE;
	char	*SO_TEXTURE;
	char	*WE_TEXTURE;
	char	*EA_TEXTURE;

	void	*mlx_image;
	void	*mlx_window;
	void	*mlx_pointer;
	void	*img_test;
	char	*img_data;
	int		img_bpp;
	int		img_endian;
	int		sz_img;

	char	*data;
	int		bpp;
	int		edian;
	int		size_line;

	struct	s_player *player;
} t_game;

/* FUNCTIONS */

void	print_keys();
void	print_title();
void	print_error(char *str);

void	init_minimap(t_game *game);
//int rgb_to_int(double r, double g, double b);
int	str_to_hex(char *str);

int	get_min(int value1, int value2);

int		key_press(int key_code, t_game *game);
int		key_release(int key_code, t_game *game);
int		stop_game(t_game *game);
void	init_hooks(t_game *game);

void	print_game_instance(t_game *game);
int		parse_arguments(int argc, char *argv[]);

void	init_game(int fd, t_game **game);
void	set_instance(int fd, t_game *game);

void	put_pixel(int x, int y, int color, t_game *game);
int		draw_loop(t_game *game);
void	move_player(t_game *game, t_player *player);
void	draw_square(int x, int y, int size, int color, t_game *game);

float	distance(float x, float y);
float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game);
bool	touch(float px, float py, t_game *game);

#endif
