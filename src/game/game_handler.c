/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:48:44 by noldiane          #+#    #+#             */
/*   Updated: 2024/11/14 13:14:55 by noldiane         ###   ########.fr       */
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

void	free_game_instance(t_game *game)
{
	int	i;
	
	i = 0;
	free_null_args(&game->NO_TEXTURE);
	free_null_args(&game->SO_TEXTURE);
	free_null_args(&game->WE_TEXTURE);
	free_null_args(&game->EA_TEXTURE);
	while (i < game->map_height && game->map[i])
		free_null_args(&game->map[i++]);
	free(game->map);
}

int	stop_game(t_game *game)
{
	free_game_instance(game);
	mlx_clear_window(game->mlx_pointer, game->mlx_window);
	mlx_destroy_window(game->mlx_pointer, game->mlx_window);
	mlx_destroy_display(game->mlx_pointer);
	mlx_loop_end(game->mlx_pointer);
	free(game->mlx_pointer);
	free(game);
	exit(EXIT_SUCCESS);
}