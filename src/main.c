/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbauer <rbauer@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:29:53 by noldiane          #+#    #+#             */
/*   Updated: 2025/02/20 16:10:23 by rbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_error_code(t_parsing *parsing_info)
{
	if (parsing_info->error_code == OK)
		return ;
	printf("Error\n");
	if (parsing_info->error_code == I_C)
		printf("Invalid character or invalid line.\n");
	else if (parsing_info->error_code == M_C_I_M)
		printf("Invalid color.\n");
	else if (parsing_info->error_code == M_T_I_M)
		printf("Invalid texture.\n");
	else if (parsing_info->error_code == P_A_S)
		printf("Player already set.\n");
	else if (parsing_info->error_code == P_N_S)
		printf("Player not set.\n");
	else if (parsing_info->error_code == M_N_C)
		printf("Invalid map content.\n");
	else if (parsing_info->error_code == L_O_S)
		printf("Line of spaces only.\n");
	else if (parsing_info->error_code == E_M)
		printf("Empty map.\n");
	else
		printf("Unknown error code.\n");
}

void	free_parsing_map(t_parsing *parsing_info)
{
	int	i;

	if (parsing_info->map)
	{
		i = 0;
		while (parsing_info->map[i])
		{
			free(parsing_info->map[i]);
			parsing_info->map[i] = NULL;
			i++;
		}
		free(parsing_info->map);
		parsing_info->map = NULL;
	}
}

void	free_parsing_info(t_parsing *parsing_info)
{
	free_parsing_map(parsing_info);
	if (parsing_info->no_texture)
		free(parsing_info->no_texture);
	if (parsing_info->so_texture)
		free(parsing_info->so_texture);
	if (parsing_info->we_texture)
		free(parsing_info->we_texture);
	if (parsing_info->ea_texture)
		free(parsing_info->ea_texture);
	parsing_info->no_texture = NULL;
	parsing_info->so_texture = NULL;
	parsing_info->we_texture = NULL;
	parsing_info->ea_texture = NULL;
	if (parsing_info->fd != -1)
	{
		close(parsing_info->fd);
		parsing_info->fd = -1;
	}
}

void	free_game_str(t_game *game)
{
	int	i;

	if (game->map)
	{
		i = 0;
		while (game->map[i])
		{
			game->map[i] = NULL;
			i++;
		}
		game->map = NULL;
	}
	game->no_texture = NULL;
	game->so_texture = NULL;
	game->we_texture = NULL;
	game->ea_texture = NULL;
}

int	main(int argc, char *argv[])
{
	t_game		*game;
	t_parsing	*parsing_info;

	print_title();
	parsing_info = malloc(sizeof(t_parsing));
	game = NULL;
	if (parsing(argc, argv, parsing_info))
	{
		print_error_code(parsing_info);
		get_next_line(parsing_info->fd, 3);
		free_parsing_info(parsing_info);
		free(parsing_info);
		return (1);
	}
	init_game(&game, &parsing_info);
	init_player_look(game, parsing_info);
	init_hooks(game);
	print_keys();
	mlx_loop(game->mlx_pointer);
	free_parsing_info(parsing_info);
	free(parsing_info);
	free_game_str(game);
	free(game);
	return (0);
}
