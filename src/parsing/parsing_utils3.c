/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbauer <rbauer@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:37:47 by rbauer            #+#    #+#             */
/*   Updated: 2025/02/20 14:42:57 by rbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parsing_line_free(char **line)
{
	if (line && line[0])
	{
		free(line[0]);
		line[0] = NULL;
	}
	if (line)
		free(line);
}

int	parsing_line_malloc(char ***line)
{
	*line = malloc(sizeof(char *) * 1);
	if (!*line)
	{
		free(line);
		print_error(ERROR_MALLOC_1);
		return (1);
	}
	*line[0] = NULL;
	return (0);
}

int	final_check(t_fill_map *fill_map_info)
{
	if (fill_map_info->started_map == 0)
	{
		fill_map_info->parsing->error_code = E_M;
		return (1);
	}
	if (fill_map_info->parsing->player_set != 1)
	{
		fill_map_info->parsing->error_code = P_N_S;
		return (1);
	}
	return (0);
}

int	handle_empty_line(t_fill_map *fill_map_info)
{
	free_null_args(&(fill_map_info->line));
	if (fill_map_info->started_map == 0)
		return (0);
	fill_map_info->ended_map = 1;
	if (test_end_map_lines(fill_map_info->parsing) == 1)
		return (1);
	return (2);
}

int	handle_non_empty_line(t_fill_map *fill_map_info)
{
	if (fill_map_info->ended_map == 1)
	{
		fill_map_info->parsing->error_code = M_N_C;
		free(fill_map_info->line);
		return (1);
	}
	fill_map_info->started_map = 1;
	if (check_map_line(fill_map_info->line, \
	fill_map_info->parsing, fill_map_info->y) == 1)
	{
		free(fill_map_info->line);
		return (1);
	}
	if (add_map_line(fill_map_info->parsing, \
	fill_map_info->line) == 1)
	{
		free(fill_map_info->line);
		return (1);
	}
	free(fill_map_info->line);
	fill_map_info->y++;
	return (0);
}
