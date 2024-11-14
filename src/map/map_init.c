/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:14:18 by noldiane          #+#    #+#             */
/*   Updated: 2024/11/14 10:38:17 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_minimap(t_game *game)
{
	int			index;
	int			current_pixel;
	const int	map_size = (get_min(WIN_WIDTH, WIN_HEIGHT) / 6) - 10;
	
	current_pixel = 0;
	while (current_pixel != map_size)
	{
		index = 1;
		while (index != map_size)
		{
			mlx_pixel_put(game->mlx_pointer, game->mlx_window, current_pixel + 11, 10 + index, game->F_COLOR);
			index++;
		}
		//mlx_pixel_put(game->mlx_pointer, game->mlx_window, current_pixel + 10, 10, 0xff3a3a);
		//mlx_pixel_put(game->mlx_pointer, game->mlx_window, 10, current_pixel + 10, 0xff3a3a);
		//mlx_pixel_put(game->mlx_pointer, game->mlx_window, map_size + 10, current_pixel + 10, 0xff3a3a);
		
		current_pixel++;
	}
	current_pixel = 0;
}