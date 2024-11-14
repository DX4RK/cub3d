/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:32:13 by noldiane          #+#    #+#             */
/*   Updated: 2024/11/14 11:42:55 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_map(char *line, t_game *game)
{
	int			i;
	char		**new_map;

	i = 0;
	new_map = malloc(sizeof(char *) * (game->map_height + 1));
	while (game->map && i < game->map_height)
	{
		new_map[i] = ft_strdup(game->map[i]);
		free(game->map[i]);
		i++;
	}
	game->map_height = game->map_height + 1;
	if (game->map)
		free(game->map);
	new_map[i] = ft_strdup(line);
	game->map = new_map;
}

int	get_color(char *str)
{
	int color;
	
	color = str_to_hex(str);
	free(str);
	return (color);
}

void	set_instance(int fd, t_game *game)
{
	int	line_count;
	char	*line;

	line_count = 0;
	while ((line = get_next_line(fd, 0)) != NULL)
	{
		if (line[0] == '1')
		{
			line_count++;
			set_map(line, game);
		}
		if (line[0] == 'F')
			game->F_COLOR = get_color(ft_substr(line, 2, ft_strlen(line) - 2));
		if (line[0] == 'C')
			game->C_COLOR = get_color(ft_substr(line, 2, ft_strlen(line) - 2));
		if (line[0] == 'N' && line[1] == 'O')
			game->NO_TEXTURE = ft_substr(line, 3, ft_strlen(line) - 3);
		if (line[0] == 'S' && line[1] == 'O')
			game->SO_TEXTURE = ft_substr(line, 3, ft_strlen(line) - 3);
		if (line[0] == 'W' && line[1] == 'E')
			game->WE_TEXTURE = ft_substr(line, 3, ft_strlen(line) - 3);
		if (line[0] == 'E' && line[1] == 'A')
			game->EA_TEXTURE = ft_substr(line, 3, ft_strlen(line) - 3);
		free(line);
	}
}

void	init_game(int fd, t_game *game)
{
	set_instance(fd, game);
}
