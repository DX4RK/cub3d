/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:29:53 by noldiane          #+#    #+#             */
/*   Updated: 2024/11/14 11:43:16 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_game		*game;
	int			fd;

	print_title();
	fd = parse_arguments(argc, argv);
	init_game_instance(fd, &game);
	game->mlx_window = mlx_new_window(game->mlx_pointer, WIN_WIDTH, WIN_HEIGHT, "Cube3D");
	init_minimap(game);
	init_hooks(game);
	print_keys();
	mlx_loop(game->mlx_pointer);
	return (0);
}
