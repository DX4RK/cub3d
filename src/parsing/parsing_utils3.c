/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:01:01 by rbauer            #+#    #+#             */
/*   Updated: 2025/02/18 12:48:16 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
t_fill_map	check_line1(char **line, t_fill_map data, t_parsing *parsing_info)
{
	if (line_is_empty(*line))
	{
		//free_null_args(line);//c'etait en commentaire
		if (!data.started_map)
		{
			free_null_args(line);
			data.return_value = 2;
		}
		else
		{
			data.ended_map = 1;
			if (test_end_map_lines(parsing_info) == 1)
				data.return_value = 1;
			data.return_value = 3;
		}
	}
	else
		data.return_value = 0;
	return (data);
}
*/

/*
t_fill_map	check_line2(char **line, int *y, t_fill_map data, t_parsing *p)
{
	data.return_value = -1;
	if (data.ended_map)
	{
		p->error_code = M_N_C;
		//free_null_args(&line);
		data.return_value = 1;
	}
	data.started_map = 1;
	if (check_map_line(*line, p, *y) == 1 && data.return_value != -1)
	{
		//free_null_args(&line);
		data.return_value = 1;
	}
	if (add_map_line(p, *line) == 1 && data.return_value != -1)
	{
		free_null_args(line);
		data.return_value = 1;
	}
	if (data.return_value == -1)
	{
		(*y)++;
		//free_null_args(&line);
		data.return_value = 0;
	}
	return (data);
}
*/

/*
int	check_line3(t_fill_map data, t_parsing *parsing_info)
{
	if (data.started_map == 0)
	{
		parsing_info->error_code = E_M;
		return (1);
	}
	if (parsing_info->player_set != 1)
	{
		parsing_info->error_code = P_N_S;
		return (1);
	}
	return (0);
}
*/