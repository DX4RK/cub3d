/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbauer <rbauer@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:48:44 by noldiane          #+#    #+#             */
/*   Updated: 2025/02/20 15:26:55 by rbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_null_args(char **arg)
{
	if (arg && *arg)
	{
		free(*arg);
		*arg = NULL;
	}
}

void	free_image(t_game *game, t_image *image)
{
	mlx_destroy_image(game->mlx_pointer, image->image);
	free(image);
}

void	free_game_instance(t_game *game)
{
	int	i;

	i = 0;
	free_null_args(&game->no_texture);
	free_null_args(&game->so_texture);
	free_null_args(&game->we_texture);
	free_null_args(&game->ea_texture);
	while (game->map[i] && i < game->map_height)
		free_null_args(&game->map[i++]);
	free(game->map);
	free_image(game, game->mlx_image);
	free_image(game, game->textures->no);
	free_image(game, game->textures->so);
	free_image(game, game->textures->we);
	free_image(game, game->textures->ea);
}

void	free_game(t_game *game)
{
	free_game_instance(game);
	free(game->ray);
	free(game->player);
	free(game->textures);
}

int	stop_game(t_game *game)
{
	free_parsing_info(*(game->parsing_info));
	free(*(game->parsing_info));
	*(game->parsing_info) = NULL;
	free_game(game);
	mlx_clear_window(game->mlx_pointer, game->mlx_window);
	mlx_destroy_window(game->mlx_pointer, game->mlx_window);
	mlx_destroy_display(game->mlx_pointer);
	mlx_loop_end(game->mlx_pointer);
	free(game->mlx_pointer);
	free(game);
	game = NULL;
	exit(EXIT_SUCCESS);
}
