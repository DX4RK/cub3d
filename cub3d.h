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
#include <fcntl.h>


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


# define RESET	"\e[0m"

# define BOLD	"\e[1m"
# define DIM	"\e[2m"
# define ITAL	"\e[3m"
# define ULINE	"\e[4m"

# define RED	"\e[31m"

# define LIGHT_RED "\033[1;31m"
# define LIGHT_ORANGE "\033[38;5;214m"

# define ERROR_MISSING_CUB "missing .cub file, or too may arguments!"
# define ERROR_WRONG_FORMAT "wrong file format!"
# define FILE_NOT_EXIST "this file does not exist, or not enough permission to read file!"
# define ERROR_MALLOC_1 "game instance allocation failed."

# define BUFFER_SIZE 5








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





/*		Parsing		*/

# define YES 1
# define NO 0
# define F 0
# define C 1
//# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define ERROR_DIRECTORY      "Error\nThe path is a directory, not a file.\n"

 typedef enum e_error
{
	OK,
	P_A_S, //player already set
	P_N_S, //player not set
	M_T_I_M, //min texture information missing aka NO SO WE EA or not exist
	M_C_I_M, //min color information missing aka F_color and c_color or invalide nbs
	E_M, //empty map
	I_C, //invalide characters
	L_O_S, //line only with spaces
	M_N_C, //map not closed
	M_N_S_L_L //map not same line lenght
}	t_ErrorType_Parsing;

 typedef struct s_parsing
{
	int						fd;
	char					**map;

	int						F_COLOR;
	int						C_COLOR;
	int						red;
	int						green;
	int						blue;
	int						color_info_ok;

	char					*NO_TEXTURE;
	char					*SO_TEXTURE;
	char					*WE_TEXTURE;
	char					*EA_TEXTURE;
	int						texter_info_ok;

	//int info_after_map

	int						player_set;//boolean
	int						player_y;
	int						player_x;

	t_ErrorType_Parsing		error_code;//quel type d'erreur à defaut à 0 donc continue la boucle
	int						map_height;
}	t_parsing;

/************************************************/






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
//int		parse_arguments(int argc, char *argv[]);
int	parse_arguments(int argc, char **argv, t_parsing *parsing_info);

void	init_game(int fd, t_game **game);
void	set_instance(int fd, t_game *game);

void	put_pixel(int x, int y, int color, t_game *game);
int		draw_loop(t_game *game);
void	move_player(t_game *game, t_player *player);
void	draw_square(int x, int y, int size, int color, t_game *game);

float	distance(float x, float y);
float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game);
bool	touch(float px, float py, t_game *game);








int	ft_isdigit(char c);





#endif
