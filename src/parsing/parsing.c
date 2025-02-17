/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbauer <rbauer@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:34:44 by noldiane          #+#    #+#             */
/*   Updated: 2025/02/17 17:10:42 by rbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_map_parsing_info(t_parsing *parsing_info)
{
	char		*line;
	int			y;
	t_fill_map	data;

	data = init_data(data);
	y = 0;
	line = get_next_line(parsing_info->fd, 0);
	while (line != NULL && parsing_info->error_code == OK)
	{
		data = check_line1(line, data, parsing_info);
		if (data.return_value == 2)
			continue ;
		else if (data.return_value == 1)
			break ;
		else
		{
			data = check_line2(line, &y, data, parsing_info);
			if (data.return_value == 1)
				return (1);
		}
		line = get_next_line(parsing_info->fd, 0);
	}
	if (check_line3(data, parsing_info) == 1)
		return (1);
	return (0);
}

int	fill_config_parsing_info(t_parsing *parsing_info)
{
	char	*line;

	line = get_next_line(parsing_info->fd, 0);
	while (line != NULL && parsing_info->error_code == OK)
	{
		if (parsing_info->color_info_ok != 1 \
		|| parsing_info->texter_info_ok != 1)
		{
			if (empty_line_spaces(line, parsing_info) == 1)
				continue ;
			if (input_data__not_map(line, parsing_info) == 1)
				return (1);
		}
		if (parsing_info->color_info_ok == 1 \
		&& parsing_info->texter_info_ok == 1)
			return (0);
		line = get_next_line(parsing_info->fd, 0);
	}
	return (0);
}

int	parse_arguments(int argc, char **argv, t_parsing *parsing_info)
{
	int		file_lenght;
	char	*file_format;

	if (argc != 2)
	{
		print_error(ERROR_MISSING_CUB);
		return (1);
	}
	file_lenght = ft_strlen(argv[1]);
	file_format = ft_substr(argv[1], (file_lenght -4), 4);
	if (!file_format)
		return (1);
	if (ft_strncmp(file_format, ".cub", 4) != 0)
	{
		free(file_format);
		print_error(ERROR_WRONG_FORMAT);
		return (1);
	}
	if (file_lenght < 5)
		free(file_format);
	if (file_lenght < 5)
		return (1);
	free(file_format);
	return (check_cub_file(argv, parsing_info));
}

int	parsing(int argc, char **argv, t_parsing *parsing_info)
{
	init_parsing(parsing_info);
	if (parse_arguments(argc, argv, parsing_info) == 1)
		return (1);
	if (fill_config_parsing_info(parsing_info) == 1)
		return (2);
	if (fill_map_parsing_info(parsing_info) == 1)
		return (3);
	if (check_map_valid(parsing_info) == 1)
		return (4);
	return (0);
}
