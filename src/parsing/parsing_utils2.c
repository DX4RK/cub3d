/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbauer <rbauer@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:12:30 by rbauer            #+#    #+#             */
/*   Updated: 2025/02/17 17:02:07 by rbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_texture(char *path, t_parsing *parsing_info, int texture_type)
{
	if (texture_type == NO_NUMBER)
		parsing_info->NO_TEXTURE = path;
	else if (texture_type == SO_NUMBER)
		parsing_info->SO_TEXTURE = path;
	else if (texture_type == WE_NUMBER)
		parsing_info->WE_TEXTURE = path;
	else if (texture_type == EA_NUMBER)
		parsing_info->EA_TEXTURE = path;
	if (parsing_info->NO_TEXTURE && parsing_info->SO_TEXTURE
		&& parsing_info->WE_TEXTURE && parsing_info->EA_TEXTURE)
	{
		parsing_info->text_ok = 1;
	}
}

int	is_in_set(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	check_cub_file(char **argv, t_parsing *parsing_info)
{
	parsing_info->fd = open(argv[1], O_RDONLY);
	if (read(parsing_info->fd, 0, 0) != 0)
	{
		print_error(FILE_NOT_EXIST);
		return (1);
	}
	return (0);
}

/*
t_fill_map	init_data(t_fill_map data)
{
	data.started_map = 0;
	data.ended_map = 0;
	return (data);
}
*/