/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbauer <rbauer@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:26:06 by noldiane          #+#    #+#             */
/*   Updated: 2025/02/20 16:19:52 by rbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* LIBRARIES */

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# include "colors.h"
# include "errors.h"
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

/* DATA */

# define DEBUG 0

# define FOV 60
# define MOVE_SPEED 1
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
	P_A_S,
	P_N_S,
	M_T_I_M,
	M_C_I_M,
	E_M,
	I_C,
	L_O_S,
	M_N_C
}	t_ErrorType_Parsing;

typedef struct s_parsing
{
	int						fd;
	char					**map;

	int						f_color;
	int						c_color;
	int						red;
	int						green;
	int						blue;
	int						col_ok;

	char					*no_texture;
	char					*so_texture;
	char					*we_texture;
	char					*ea_texture;
	int						text_ok;

	int						player_set;
	int						player_y;
	int						player_x;
	int						player_letter;

	t_ErrorType_Parsing		error_code;
	int						map_height;
}	t_parsing;

typedef struct s_fill_map
{
	t_parsing	*parsing;
	char		*line;
	int			started_map;
	int			ended_map;
	int			y;
}	t_fill_map;

typedef struct s_ray
{
	int		flag;
	double	ray_ngl;
	double	distance;
	double	horiz_x;
	double	horiz_y;
	double	vert_x;
	double	vert_y;
}	t_ray;

typedef struct s_image
{
	int		width;
	int		height;
	char	*data;
	int		bpp;
	int		edian;
	int		size_line;
	void	*image;
}	t_image;

typedef struct s_textures
{
	struct s_image	*no;
	struct s_image	*so;
	struct s_image	*we;
	struct s_image	*ea;
}	t_textures;

typedef struct s_position
{
	double	x;
	double	y;
}	t_position;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	shortest_distance;

	double	angle;
	float	fov_rd;

	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;

	bool	rotate_left;
	bool	rotate_right;

	bool	touching_wall;
}	t_player;

typedef struct s_game
{
	int					map_height;

	char				**map;

	int					f_color;
	int					c_color;

	char				*no_texture;
	char				*so_texture;
	char				*we_texture;
	char				*ea_texture;

	void				*mlx_window;
	void				*mlx_pointer;

	struct s_image		*mlx_image;

	struct s_ray		*ray;
	struct s_player		*player;
	struct s_textures	*textures;

	struct s_parsing	**parsing_info;
}	t_game;

/* FUNCTIONS */

void	print_keys(void);
void	print_title(void);
void	print_error(char *str);
void	set_player_angle(t_player *player, double angle_degrees);

int		draw_loop(t_game *game);
int		rgb_to_int(int r, int g, int b);
int		get_min(int value1, int value2);
int		key_press(int key_code, t_game *game);
int		key_release(int key_code, t_game *game);
int		stop_game(t_game *game);
int		parsing(int argc, char **argv, t_parsing *parsing_info);
int		wall_hit(float x, float y, t_game *game);
int		get_wall_color(t_game *game, int tex_x, int tex_y);
int		unit_circle(float angle, char c);

float	nor_angle(float angle);

void	init_hooks(t_game *game);
void	print_game_instance(t_game *game);
void	init_game(t_game **game, t_parsing **parsing_info);
void	put_pixel(int x, int y, int color, t_game *game);
void	update_player(t_game *game, t_player *player);
void	cast_rays(t_game *game);
void	render_wall(t_game *game, int ray);
void	cast_rays(t_game *game);
void	init_parsing(t_parsing *parsing_info);
void	load_texture(t_game *game, char *path, t_image *image);
void	fill_game(t_game *game, t_parsing *parsing_info);
void	draw_floor_ceiling(t_game *game, int ray, int t_pix, int b_pix);
void	set_texture(char *path, t_parsing *parsing_info, int texture_type);
void	free_null_args(char **arg);
void	init_player_look(t_game *game, t_parsing *parsing_info);

t_image	*get_texture(int flag, t_game *game);

/* PARSING UTILS */

void	free_parsing_info(t_parsing *parsing_info);
void	parsing_line_free(char **line);
int		parsing_line_malloc(char ***line);
int		handle_empty_line(t_fill_map *fill_map_info);
int		handle_non_empty_line(t_fill_map *fill_map_info);
int		final_check(t_fill_map *fill_map_info);
int		check_cub_file(char **argv, t_parsing *parsing_info);
int		parse_arguments(int argc, char **argv, t_parsing *parsing_info);
int		empty_line_spaces(char *line, t_parsing *parsing_info);
void	skip_spaces(const char *line, int *i);
int		parse_color_value(char *line, t_parsing *parsing_info, int *i);
int		save_color(t_parsing *parsing_info, int color_type);
int		input_color(char *line, t_parsing *parsing_info, int i, int color_type);
int		verif_color(char *line, t_parsing *parsing_info, int color_type);
char	*extract_texture_path(char *line, int *i);
int		check_texture_file_valid(char *path);
int		check_xpm_extension(const char *path);
int		verif_texture(char *line, t_parsing *parsing_info, int texture_type);
int		input_data__not_map(char *line, t_parsing *parsing_info);
int		line_is_empty(char *line);
int		add_map_line(t_parsing *parsing_info, char *str);
int		check_map_line(char *line, t_parsing *parsing_info, int y);
int		test_end_map_lines(t_parsing *parsing_info);
int		fill_map_parsing_info(t_parsing *parsing_info);
int		fill_config_parsing_info(t_parsing *parsing_info, char *line);
int		ft_strlen__no_n(const char *str);
char	get_neighbor_char(t_parsing *parsing_info, int y, int x, int nb_y);
int		is_in_set(char c, char *str);
int		check_neighbor(t_parsing *parsing_info, \
		int y, int x, char *valid_neighbors);
int		check_player_rules(t_parsing *parsing_info, int y, int x, int line_len);
int		check_floor_rules(t_parsing *parsing_info, int y, int x, int line_len);
int		check_space_rules(t_parsing *parsing_info, int y, int x);
int		verify_cell_and_neighbors(t_parsing *parsing_info, \
		int y, int x, int line_len);
int		check_map_line_valid(t_parsing *parsing_info, int y, int nb_y);
int		check_map_valid(t_parsing *parsing_info);
int		read_map(t_fill_map *fill_map_info);
void	init_fill_map(t_fill_map *fill_map_info, t_parsing *parsing_info);

#endif
