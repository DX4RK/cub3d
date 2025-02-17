/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbauer <rbauer@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:56:14 by rbauer            #+#    #+#             */
/*   Updated: 2025/02/17 15:58:22 by rbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	count_spaces(char *line, int *space, int *other_than_space)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			(*space)++;
		else if (line[i] != '\n')
			(*other_than_space)++;
		i++;
	}
}

int	empty_line_spaces(char *line, t_parsing *parsing_info)
{
	int	other_than_space;
	int	space;

	other_than_space = 0;
	space = 0;
	count_spaces(line, &space, &other_than_space);
	if (space > 0 && other_than_space == 0)
	{
		parsing_info->error_code = L_O_S;
		free(line);
		return (1);
	}
	if (space == 0 && other_than_space == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}

void	skip_spaces(const char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
}
