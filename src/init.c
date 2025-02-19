/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:20:33 by noldiane          #+#    #+#             */
/*   Updated: 2025/02/14 14:43:52 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player *player)
{
	player->angle = PI;
	player->fov_rd = (FOV * PI) / 180;
	player->dir_x = 0;
	player->dir_y = -1;
	player->plane_x = 0.66;
	player->plane_y = 0;
	player->shortest_distance = 0;
	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->rotate_left = false;
	player->rotate_right = false;
	player->touching_wall = false;
}

void	init_parsing(t_parsing *parsing_info)
{
	parsing_info->fd = -1;
	parsing_info->map = NULL;
	parsing_info->F_COLOR = -1;
	parsing_info->C_COLOR = -1;
	parsing_info->red = -1;
	parsing_info->green = -1;
	parsing_info->blue = -1;
	parsing_info->col_ok = -1;
	parsing_info->NO_TEXTURE = NULL;
	parsing_info->SO_TEXTURE = NULL;
	parsing_info->WE_TEXTURE = NULL;
	parsing_info->EA_TEXTURE = NULL;
	parsing_info->text_ok = -1;
	parsing_info->player_set = -1;
	parsing_info->player_x = -1;
	parsing_info->player_y = -1;
	parsing_info->error_code = OK;
	parsing_info->map_height = 0;
}

void	init_game_instance(t_game *game)
{
	init_player(game->player);
	game->mlx_pointer = mlx_init();
	game->mlx_window = mlx_new_window(game->mlx_pointer, \
		WIN_WIDTH, WIN_HEIGHT, "cub3D");
	game->mlx_image->image = mlx_new_image(game->mlx_pointer, \
		WIN_WIDTH, WIN_HEIGHT);
	game->mlx_image->data = mlx_get_data_addr(game->mlx_image->image, \
		&game->mlx_image->bpp, &game->mlx_image->size_line, \
		&game->mlx_image->edian);
	load_texture(game, game->NO_TEXTURE, game->textures->NO);
	load_texture(game, game->SO_TEXTURE, game->textures->SO);
	load_texture(game, game->WE_TEXTURE, game->textures->WE);
	load_texture(game, game->EA_TEXTURE, game->textures->EA);
	mlx_put_image_to_window(game->mlx_pointer, game->mlx_window, \
		game->mlx_image->image, 0, 0);
}

void	init_instance(t_game *game, t_parsing *parsing_info)
{
	game->map_height = 0;
	game->F_COLOR = 0;
	game->C_COLOR = 0;
	game->map = NULL;
	game->NO_TEXTURE = NULL;
	game->SO_TEXTURE = NULL;
	game->WE_TEXTURE = NULL;
	game->EA_TEXTURE = NULL;
	game->ray = malloc(sizeof(t_ray));
	game->player = malloc(sizeof(t_player));
	game->mlx_image = malloc(sizeof(t_image));
	game->textures = malloc(sizeof(t_textures));
	game->textures->NO = malloc(sizeof(t_image));
	game->textures->SO = malloc(sizeof(t_image));
	game->textures->WE = malloc(sizeof(t_image));
	game->textures->EA = malloc(sizeof(t_image));
	fill_game(game, parsing_info);
	init_game_instance(game);
}

void	init_game(t_game **game, t_parsing **parsing_info)
{
	*game = malloc(sizeof(t_game));
	if (!(*game))
	{
		print_error(ERROR_MALLOC_1);
		exit (EXIT_FAILURE);
	}
	init_instance(*game, *parsing_info);
	(*game)->parsing_info = parsing_info;
}
