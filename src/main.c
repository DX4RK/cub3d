/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:29:53 by noldiane          #+#    #+#             */
/*   Updated: 2025/02/15 15:05:27 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	unit_circle(float angle, char c)
{
	if (c == 'x')
	{
		if (angle > 0 && angle < PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (PI / 2) && angle < (3 * PI) / 2)
			return (1);
	}
	return (0);
}

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

void	free_parsing_info(t_parsing *parsing_info)
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
	if (parsing_info->NO_TEXTURE)
		free(parsing_info->NO_TEXTURE);
	if (parsing_info->SO_TEXTURE)
		free(parsing_info->SO_TEXTURE);
	if (parsing_info->WE_TEXTURE)
		free(parsing_info->WE_TEXTURE);
	if (parsing_info->EA_TEXTURE)
		free(parsing_info->EA_TEXTURE);
	parsing_info->NO_TEXTURE = NULL;
	parsing_info->SO_TEXTURE = NULL;
	parsing_info->WE_TEXTURE = NULL;
	parsing_info->EA_TEXTURE = NULL;
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
	game->NO_TEXTURE = NULL;
	game->SO_TEXTURE = NULL;
	game->WE_TEXTURE = NULL;
	game->EA_TEXTURE = NULL;
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
		free_parsing_info(parsing_info);
		free(parsing_info);
		printf("DEBUG\n");//debug
		return (1);
	}
	init_game(&game, &parsing_info);
	print_game_instance(game);
	if (parsing_info->player_letter == 'N')
		set_player_angle(game->player, 0);
	else if (parsing_info->player_letter == 'S')
		set_player_angle(game->player, 180);
	else if (parsing_info->player_letter == 'W')
		set_player_angle(game->player, 270);
	else if (parsing_info->player_letter == 'E')
		set_player_angle(game->player, 90);
	init_hooks(game);
	print_keys();
	mlx_loop(game->mlx_pointer);
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	printf("\n\n\n HERE \n\n\n");
	free_parsing_info(parsing_info);
	free(parsing_info);
	free_game_str(game);
	free(game);
	return (0);
}
