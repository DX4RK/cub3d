/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:26:06 by noldiane          #+#    #+#             */
/*   Updated: 2025/02/13 14:01:23 by noldiane         ###   ########.fr       */
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

# define FOV 60
# define MOVE_SPEED 1;
# define ROTATE_SPEED 0.015

# define TILE_SIZE 64
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

# define NO_NUMBER 0
# define SO_NUMBER 1
# define WE_NUMBER 2
# define EA_NUMBER 3

/* STRUCTURES */

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
	M_N_C //map not closed
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
	int						player_letter;

	t_ErrorType_Parsing		error_code;//quel type d'erreur à defaut à 0 donc continue la boucle
	int						map_height;
}	t_parsing;

typedef struct s_ray
{
 double ray_ngl; // ray angle
 double distance; // distance to the wall
 double	horiz_x;
	double	horiz_y;
	double	vert_x;
	double	vert_y;
 int  flag;  // flag for the wall
} t_ray;

typedef struct s_image
{
	int		width;
	int		height;
	char	*data;
	int		bpp;
	int		edian;
	int		size_line;
	void	*image;
} t_image;

typedef struct s_textures
{
	struct s_image *NO;
	struct s_image *SO;
	struct s_image *WE;
	struct s_image *EA;
} t_textures;

typedef	struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int	test;
	double	shortest_distance;

	double 	angle;
	float	fov_rd;

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

	void	*mlx_window;
	void	*mlx_pointer;
	void	*img_test;
	char	*img_data;
	int		img_bpp;
	int		img_endian;
	int		sz_img;

	struct	s_image *mlx_image;

	struct	s_ray *ray;
	struct	s_player *player;
	struct	s_textures *textures;
} t_game;

/* FUNCTIONS */

void	print_keys();
void	print_title();
void	print_error(char *str);

void	init_minimap(t_game *game);
int rgb_to_int(int r, int g, int b);
int	str_to_hex(char *str);

void set_player_angle(t_player *player, double angle_degrees);

int	get_min(int value1, int value2);

int		key_press(int key_code, t_game *game);
int		key_release(int key_code, t_game *game);
int		stop_game(t_game *game);
void	init_hooks(t_game *game);

void	print_game_instance(t_game *game);
void	init_game(t_game **game, t_parsing *parsing_info);
void	set_instance(int fd, t_game *game);

void	put_pixel(int x, int y, int color, t_game *game);
int		draw_loop(t_game *game);
void	move_player(t_game *game, t_player *player);
void	draw_square(int x, int y, int size, int color, t_game *game);

float	distance(float x, float y);
float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game);
bool	touch(float px, float py, t_game *game);

void cast_rays(t_game *game);
void render_wall(t_game *game, int ray);
int	wall_hit(float x, float y, t_game *game);
void cast_rays(t_game *game);
float nor_angle(float angle);

void	init_parsing(t_parsing *parsing_info);
int	parsing(int argc, char **argv, t_parsing *parsing_info);

void	fill_game(t_game *game, t_parsing *parsing_info);

/* PARSING UTILS */

int parse_arguments(int argc, char **argv, t_parsing *parsing_info);
int empty_line_spaces(char *line, t_parsing *parsing_info);
void skip_spaces(const char *line, int *i);
int parse_color_value(char *line, t_parsing *parsing_info, int *i);
int save_color(t_parsing *parsing_info, int color_type);
int input_color(char *line, t_parsing *parsing_info, int i, int color_type);
int verif_color(char *line, t_parsing *parsing_info, int color_type);
char *extract_texture_path(char *line, int *i);
int check_texture_file_valid(char *path);
int check_xpm_extension(const char *path);
int verif_texture(char *line, t_parsing *parsing_info, int texture_type);
int input_data__NOT_MAP(char *line, t_parsing *parsing_info);
int line_is_empty(char *line);
int add_map_line(t_parsing *parsing_info, char *str);
int check_map_line(char *line, t_parsing *parsing_info, int y);
int test_end_map_lines(t_parsing *parsing_info);
int fill_map_parsing_info(t_parsing *parsing_info);
int fill_config_parsing_info(t_parsing *parsing_info);
int ft_strlen__NO_N(const char *str);
char get_neighbor_char(t_parsing *parsing_info, int y, int x, int nb_y);
int is_in_set(char c, char *str);
int check_neighbor(t_parsing *parsing_info, int y, int x, char *valid_neighbors);
int check_player_rules(t_parsing *parsing_info, int y, int x, int line_len);
int check_floor_rules(t_parsing *parsing_info, int y, int x, int line_len);
int check_space_rules(t_parsing *parsing_info, int y, int x);
int verify_cell_and_neighbors(t_parsing *parsing_info, int y, int x, int line_len);
int check_map_line_valid(t_parsing *parsing_info, int y, int nb_y);
int check_map_valid(t_parsing *parsing_info);

#endif
