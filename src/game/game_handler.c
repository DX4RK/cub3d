/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbauer <rbauer@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:48:44 by noldiane          #+#    #+#             */
/*   Updated: 2025/02/18 16:39:29 by rbauer           ###   ########.fr       */
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
	free_null_args(&game->NO_TEXTURE);
	free_null_args(&game->SO_TEXTURE);
	free_null_args(&game->WE_TEXTURE);
	free_null_args(&game->EA_TEXTURE);
	while (game->map[i] && i < game->map_height)
		free_null_args(&game->map[i++]);
	free(game->map);
	free_image(game, game->mlx_image);
	free_image(game, game->textures->NO);
	free_image(game, game->textures->SO);
	free_image(game, game->textures->WE);
	free_image(game, game->textures->EA);
}

void	free_game(t_game *game)
{
	free_game_instance(game);
	free(game->ray);
	free(game->player);
	free(game->textures);
}

void	free_array(char ***array_ptr)
{
	int		i;
	char	**array;

	if (!array_ptr || !*array_ptr)
		return ;
	array = *array_ptr;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	*array_ptr = NULL;
}

int	stop_game(t_game *game)
{
	free_game(game);
	mlx_clear_window(game->mlx_pointer, game->mlx_window);
	mlx_destroy_window(game->mlx_pointer, game->mlx_window);
	mlx_destroy_display(game->mlx_pointer);
	mlx_loop_end(game->mlx_pointer);
	free(game->mlx_pointer);
	exit(EXIT_SUCCESS);
}
