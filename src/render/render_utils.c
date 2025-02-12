/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:04:15 by noldiane          #+#    #+#             */
/*   Updated: 2025/02/10 14:37:56 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void put_pixel(int x, int y, int color, t_game *game)
{
    char *dst;

    if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return;

    dst = game->mlx_image->data + (y * game->mlx_image->size_line + x * (game->mlx_image->bpp / 8));
    *(unsigned int *)dst = color;
}


void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int	i;

	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x, y + i, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + size, y + i, color, game);
		i++;
	}
	i = 0;
	while (i <= size)
	{
		put_pixel(x + i, y + size, color, game);
		i++;
	}
}
