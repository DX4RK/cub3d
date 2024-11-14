/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:26:06 by noldiane          #+#    #+#             */
/*   Updated: 2024/11/14 13:14:55 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

/* LIBRARIES */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

# include "colors.h"
# include "errors.h"
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

/* DATA */

# define WIN_WIDTH 640
# define WIN_HEIGHT 480

# define FORWARD_KEY 122
# define BACK_KEY 115
# define LEFT_KEY 113
# define RIGHT_KEY 100

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

typedef struct s_game
{
	int		map_height;

	char	**map;

	int		F_COLOR;
	int		C_COLOR;

	char	*NO_TEXTURE;
	char	*SO_TEXTURE;
	char	*WE_TEXTURE;
	char	*EA_TEXTURE;

	void	*mlx_window;
	void	*mlx_pointer;
} t_game;

/* FUNCTIONS */

void	print_keys();
void	print_title();
void	print_error(char *str);

void	init_minimap(t_game *game);
//int rgb_to_int(double r, double g, double b);
int	str_to_hex(char *str);

int	get_min(int value1, int value2);

int	key_pressed(int	key_code, t_game *game);
int	stop_game(t_game *game);
void	init_hooks(t_game *game);

void	print_game_instance(t_game *game);
int		parse_arguments(int argc, char *argv[]);

void	init_game(int fd, t_game *game);
void	init_game_instance(int fd, t_game **game);

#endif
