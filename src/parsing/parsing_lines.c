/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbauer <rbauer@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:48:34 by rbauer            #+#    #+#             */
/*   Updated: 2025/02/17 15:55:07 by rbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	line_is_empty(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	get_count(t_parsing *parsing_info)
{
	int		count;

	count = 0;
	if (parsing_info->map)
		while (parsing_info->map[count])
			count++;
	return (count);
}

int	add_map_line(t_parsing *parsing_info, char *str)
{
	int			i;
	char		**new_map;
	const int	count = get_count(parsing_info);

	new_map = malloc(sizeof(char *) * (count + 1 + 1));
	if (!new_map)
		return (1);
	i = 0;
	while (i < count)
	{
		new_map[i] = parsing_info->map[i];
		i++;
	}
	new_map[count] = ft_strdup(str);
	if (!new_map[count])
	{
		free(new_map);
		return (1);
	}
	new_map[count + 1] = NULL;
	if (parsing_info->map)
		free(parsing_info->map);
	parsing_info->map = new_map;
	return (0);
}

int	check_map_line(char *l, t_parsing *parsing_info, int y)
{
	int	i;

	i = 0;
	while (l[i] && l[i] != '\n')
	{
		if (l[i] == 'N' || l[i] == 'S' || l[i] == 'E' || l[i] == 'W')
		{
			if (parsing_info->player_set != -1)
			{
				parsing_info->error_code = P_A_S;
				return (1);
			}
			parsing_info->player_set = 1;
			parsing_info->player_y = y;
			parsing_info->player_x = i;
			parsing_info->player_letter = l[i];
		}
		else if (l[i] != ' ' && l[i] != '1' && l[i] != '0')
		{
			parsing_info->error_code = I_C;
			return (1);
		}
		i++;
	}
	return (0);
}

int	test_end_map_lines(t_parsing *parsing_info)
{
	char	*line;

	line = get_next_line(parsing_info->fd, 0);
	while (line != NULL)
	{
		if (!line_is_empty(line))
		{
			parsing_info->error_code = M_N_C;
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(parsing_info->fd, 0);
	}
	return (0);
}
