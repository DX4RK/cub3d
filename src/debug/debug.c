/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbauer <rbauer@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:27:06 by noldiane          #+#    #+#             */
/*   Updated: 2025/02/20 15:23:09 by rbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_game_instance(t_game *game)
{
	int	map_index;

	map_index = 0;
	printf("f_color: %d\n", game->f_color);
	printf("c_color: %d\n", game->c_color);
	printf("no_texture: %s\n", game->no_texture);
	printf("so_texture: %s\n", game->so_texture);
	printf("we_texture: %s\n", game->we_texture);
	printf("ea_texture: %s\n", game->ea_texture);
	while (game->map[map_index])
	{
		printf("%s", game->map[map_index]);
		map_index++;
	}
	printf("\n");
}
