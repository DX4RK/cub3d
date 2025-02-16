/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:27:06 by noldiane          #+#    #+#             */
/*   Updated: 2025/02/14 14:50:09 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_game_instance(t_game *game)
{
	int	map_index;

	map_index = 0;
	printf("F_COLOR: %d\n", game->F_COLOR);
	printf("C_COLOR: %d\n", game->C_COLOR);
	printf("NO_TEXTURE: %s\n", game->NO_TEXTURE);
	printf("SO_TEXTURE: %s\n", game->SO_TEXTURE);
	printf("WE_TEXTURE: %s\n", game->WE_TEXTURE);
	printf("EA_TEXTURE: %s\n", game->EA_TEXTURE);
	while (game->map[map_index])
	{
		printf("%s", game->map[map_index]);
		map_index++;
	}
	printf("\n");
}
