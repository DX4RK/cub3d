/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:14:18 by noldiane          #+#    #+#             */
/*   Updated: 2025/01/28 17:07:00 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/*
void	draw_square2(int x, int y, int size, int color, t_game *game)
{
	int i;
	int b;

	b = 0;
	while (b < size)
	{
		i = 0;
		while (i < size)
		{
			put_pixel(x + i, y + b, color, game);
			i++;
		}
		b++;
	}
}

void	put_pixel_mini(int x, int y, int color, int width, int height, t_game *game)
{
	if (x >= width || y >= height || x < 0 || y < 0)
		return;

	int	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	draw_square3(int x, int y, int size, int color, int width, int height, t_game *game)
{
	int i;
	int b;

	b = 0;
	while (b < size)
	{
		i = 0;
		while (i < size)
		{
			put_pixel_mini(x + i, y + b, color, width, height, game);
			i++;
		}
		b++;
	}
}

void	init_minimap(t_game *game)
{
	int	x;
	int	y;
	const int	map_size = (get_min(WIN_WIDTH, WIN_HEIGHT) / 6) - 10;

	draw_square2(10, 10, map_size, 0x0000, game);
	x = 0;
	y = 0;
	while (game->map[y])
	{
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				draw_square3(x * 10, y * 10, 10, game->F_COLOR, map_size, map_size, game);
			x++;
		}
		y++;
		x = 0;
	}

}
*/
