/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:56:14 by rbauer            #+#    #+#             */
/*   Updated: 2025/02/18 12:54:48 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	empty_line_spaces(char *line, t_parsing *parsing_info)
{
	int	i;
	int	other_than_space;
	int	space;

	i = 0;
	other_than_space = 0;
	space = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			space++;
		else if (line[i] != '\n')
			other_than_space++;
		i++;
	}
	if (space > 0 && other_than_space == 0)
	{
		parsing_info->error_code = L_O_S;
		return (1);
	}
	if (space == 0 && other_than_space == 0)
		return (1);
	return (0);
}

void	skip_spaces(const char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
}
