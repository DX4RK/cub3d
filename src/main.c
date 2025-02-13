/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:29:53 by noldiane          #+#    #+#             */
/*   Updated: 2025/02/13 14:17:04 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_game		*game;
	t_parsing	*parsing_info;

	print_title();
	parsing_info = malloc(sizeof(t_parsing));
	if (parsing(argc, argv, parsing_info))
		return (1);
	init_game(&game, parsing_info);
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
	return (0);
}
