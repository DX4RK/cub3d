/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:20:33 by noldiane          #+#    #+#             */
/*   Updated: 2025/01/15 23:35:44 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_hooks(t_game *game)
{
	mlx_hook(game->mlx_window, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->mlx_window, KeyRelease, KeyReleaseMask, key_release, game);
	mlx_hook(game->mlx_window, DestroyNotify, ButtonPressMask, stop_game, game);
	mlx_loop_hook(game->mlx_pointer, draw_loop, game);
}

void	init_instance(t_game *game)
{
	game->map_height = 0;

	game->F_COLOR = 0;
	game->C_COLOR = 0;
	game->camera_x = 0;
	game->camera_y = 0;

	game->map = NULL;
	game->NO_TEXTURE = NULL;
	game->SO_TEXTURE = NULL;
	game->WE_TEXTURE = NULL;
	game->EA_TEXTURE = NULL;
	game->player = malloc(sizeof(t_player));
}

void	init_player(t_player *player)
{
	player->x = WIN_WIDTH / 2;
	player->y = WIN_HEIGHT / 2;
	player->angle = PI / 2;

	player->key_up = false;
	player->key_down = false;
	player->key_left = false;
	player->key_right = false;
	player->rotate_left = false;
	player->rotate_right = false;
}

void	init_game_instance(t_game *game)
{
	init_instance(game);
	init_player(game->player);
	game->mlx_pointer = mlx_init();
	game->mlx_window = mlx_new_window(game->mlx_pointer, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	game->mlx_image = mlx_new_image(game->mlx_pointer, WIN_WIDTH, WIN_HEIGHT);
	game->data = mlx_get_data_addr(game->mlx_image, &game->bpp, &game->size_line, &game->edian);
	mlx_put_image_to_window(game->mlx_pointer, game->mlx_window, game->mlx_image, 0, 0);
}

void	init_game(int fd, t_game **game)
{
	*game = malloc(sizeof(t_game));
	if (!(*game))
	{
		print_error(ERROR_MALLOC_1);
		exit (EXIT_FAILURE);
	}
	init_game_instance(*game);
	set_instance(fd, *game);
}
