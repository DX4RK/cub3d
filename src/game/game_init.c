/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:32:13 by noldiane          #+#    #+#             */
/*   Updated: 2025/01/29 11:17:44 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strdup2(const char *str)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!ptr)
	{
		return (NULL);
	}
	while (str[i] != '\0' && str[i] != '\n')
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}


char	**clone_map(t_parsing *parsing_info)
{
	int i;
	char **map;

	i = 0;
	map = malloc(sizeof(char *) * parsing_info->map_height + 1);
	while (parsing_info->map[i] && i <= parsing_info->map_height)
	{
		map[i] = ft_strdup2(parsing_info->map[i]);
		i++;
	}
	map[i] = 0;
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
