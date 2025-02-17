/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbauer <rbauer@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:38:42 by rbauer            #+#    #+#             */
/*   Updated: 2025/02/17 16:14:00 by rbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_neighbor(t_parsing *parsing_info,
	int y, int x, char *valid_neighbors)
{
	char	neighbor;

	neighbor = get_neighbor_char(parsing_info, y, x, parsing_info->map_height);
	if (!is_in_set(neighbor, valid_neighbors))
	{
		parsing_info->error_code = M_N_C;
		return (1);
	}
	return (0);
}

int	check_player_rules(t_parsing *parsing_info,
	int y, int x, int line_len)
{
	char	*valid_neighbors;

	if (y == 0 || y == parsing_info->map_height - 1
		|| x == 0 || x == line_len - 1)
	{
		parsing_info->error_code = M_N_C;
		return (1);
	}
	valid_neighbors = "10NSEW";
	if (check_neighbor(parsing_info, y - 1, x, valid_neighbors))
		return (1);
	if (check_neighbor(parsing_info, y + 1, x, valid_neighbors))
		return (1);
	if (check_neighbor(parsing_info, y, x - 1, valid_neighbors))
		return (1);
	if (check_neighbor(parsing_info, y, x + 1, valid_neighbors))
		return (1);
	return (0);
}

int	check_floor_rules(t_parsing *parsing_info,
	int y, int x, int line_len)
{
	char	*valid_neighbors;

	if (y == 0 || y == parsing_info->map_height - 1
		|| x == 0 || x == line_len - 1)
	{
		parsing_info->error_code = M_N_C;
		return (1);
	}
	valid_neighbors = "10NSEW";
	if (check_neighbor(parsing_info, y - 1, x, valid_neighbors))
		return (1);
	if (check_neighbor(parsing_info, y + 1, x, valid_neighbors))
		return (1);
	if (check_neighbor(parsing_info, y, x - 1, valid_neighbors))
		return (1);
	if (check_neighbor(parsing_info, y, x + 1, valid_neighbors))
		return (1);
	return (0);
}

int	check_space_rules(t_parsing *parsing_info,
	int y, int x)
{
	char	*valid_neighbors;

	valid_neighbors = " 1";
	if (check_neighbor(parsing_info, y - 1, x, valid_neighbors) == 1)
		return (1);
	if (check_neighbor(parsing_info, y + 1, x, valid_neighbors) == 1)
		return (1);
	if (check_neighbor(parsing_info, y, x - 1, valid_neighbors) == 1)
		return (1);
	if (check_neighbor(parsing_info, y, x + 1, valid_neighbors) == 1)
		return (1);
	return (0);
}

int	check_map_line_valid(t_parsing *parsing_info, int y, int nb_y)
{
	int		x;
	char	*line;
	int		line_len;

	line = parsing_info->map[y];
	if (!line)
		return (0);
	line_len = ft_strlen__no_n(line);
	parsing_info->map_height = nb_y;
	x = 0;
	while (x < line_len)
	{
		if (verify_cell_and_neighbors(parsing_info, y, x, line_len) == 1)
			return (1);
		x++;
	}
	return (0);
}
