/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:29:53 by noldiane          #+#    #+#             */
/*   Updated: 2025/02/10 15:23:55 by noldiane         ###   ########.fr       */
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
	//fd = parse_arguments(argc, argv, gam);
	init_game(&game, parsing_info);
	print_game_instance(game);
	init_hooks(game);
	//init_minimap(game);
	//draw_square(WIN_WIDTH / 2, WIN_HEIGHT / 2, 10, 0x00FF00, game);
	print_keys();
	mlx_loop(game->mlx_pointer);
	return (0);
}
