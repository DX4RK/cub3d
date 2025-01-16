/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:29:53 by noldiane          #+#    #+#             */
/*   Updated: 2025/01/16 00:21:34 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_game		*game;
	int			fd;

	print_title();
	fd = parse_arguments(argc, argv);

	init_game(fd, &game);
	init_hooks(game);

	//draw_square(WIN_WIDTH / 2, WIN_HEIGHT / 2, 10, 0x00FF00, game);
	print_keys();
	mlx_loop(game->mlx_pointer);
	return (0);
}
