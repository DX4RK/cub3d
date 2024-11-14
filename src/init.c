/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:20:33 by noldiane          #+#    #+#             */
/*   Updated: 2024/11/14 13:14:55 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_hooks(t_game *game)
{
	mlx_hook(game->mlx_window, KeyPress, KeyPressMask, key_pressed, game);
	mlx_hook(game->mlx_window, DestroyNotify, ButtonPressMask, stop_game, game);
}

void	init_instance(t_game *game)
{
	game->map_height = 0;

	game->F_COLOR = 0;
	game->C_COLOR = 0;

	game->map = NULL;
	game->NO_TEXTURE = NULL;
	game->SO_TEXTURE = NULL;
	game->WE_TEXTURE = NULL;
	game->EA_TEXTURE = NULL;

	game->mlx_pointer = mlx_init();
}

void	init_game_instance(int fd, t_game **game)
{
	*game = malloc(sizeof(t_game));
	if (!(*game))
	{
		print_error(ERROR_MALLOC_1);
		exit (EXIT_FAILURE);
	}
	init_instance(*game);
	init_game(fd, *game);
}
