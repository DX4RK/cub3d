/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbauer <rbauer@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:39:12 by rbauer            #+#    #+#             */
/*   Updated: 2025/02/20 16:14:00 by rbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_fill_map(t_fill_map *fill_map_info, t_parsing *parsing_info)
{
	fill_map_info->parsing = parsing_info;
	fill_map_info->line = NULL;
	fill_map_info->started_map = 0;
	fill_map_info->ended_map = 0;
	fill_map_info->y = 0;
}

int	read_map(t_fill_map *fill_map_info)
{
	int	return_value;

	return_value = 0;
	while (1)
	{
		fill_map_info->line = get_next_line(fill_map_info->parsing->fd, 0);
		if (fill_map_info->line == NULL \
		|| fill_map_info->parsing->error_code != OK)
			break ;
		if (line_is_empty(fill_map_info->line) == 1)
		{
			return_value = handle_empty_line(fill_map_info);
			if (return_value == 1)
				return (1);
			if (return_value == 2)
				break ;
		}
		else
		{
			if (handle_non_empty_line(fill_map_info) != 0)
				return (1);
		}
	}
	return (0);
}
