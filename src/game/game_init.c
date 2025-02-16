/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:32:13 by noldiane          #+#    #+#             */
/*   Updated: 2025/02/14 14:50:55 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**clone_map(t_parsing *parsing_info)
{
	int		i;
	char	**map;

	i = 0;
	map = malloc(sizeof(char *) * (parsing_info->map_height + 1));
	while (i < parsing_info->map_height)
	{
		map[i] = ft_strdup(parsing_info->map[i]);
		i++;
	}
	map[i] = NULL;
	return (map);
}

void	fill_game(t_game *game, t_parsing *parsing_info)
{
	game->F_COLOR = parsing_info->F_COLOR;
	game->C_COLOR = parsing_info->C_COLOR;
	game->NO_TEXTURE = ft_strdup(parsing_info->NO_TEXTURE);
	game->SO_TEXTURE = ft_strdup(parsing_info->SO_TEXTURE);
	game->WE_TEXTURE = ft_strdup(parsing_info->WE_TEXTURE);
	game->EA_TEXTURE = ft_strdup(parsing_info->EA_TEXTURE);
	game->map = clone_map(parsing_info);
	game->map_height = parsing_info->map_height;
	game->player->pos_x = (parsing_info->player_x * TILE_SIZE) + 10;
	game->player->pos_y = (parsing_info->player_y * TILE_SIZE) + 10;
}

void	load_texture(t_game *game, char *path, t_image *image)
{
	image->image = mlx_xpm_file_to_image(game->mlx_pointer, path, \
		&image->width, &image->height);
	image->data = mlx_get_data_addr(image->image, &image->bpp, \
		&image->size_line, &image->edian);
}

void	init_hooks(t_game *game)
{
	mlx_hook(game->mlx_window, KeyPress, KeyPressMask, key_press, game);
	mlx_hook(game->mlx_window, KeyRelease, KeyReleaseMask, key_release, game);
	mlx_hook(game->mlx_window, DestroyNotify, ButtonPressMask, stop_game, game);
	mlx_loop_hook(game->mlx_pointer, draw_loop, game);
}
