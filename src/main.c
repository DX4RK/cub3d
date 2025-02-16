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
