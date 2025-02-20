/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbauer <rbauer@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:34:44 by noldiane          #+#    #+#             */
/*   Updated: 2025/02/20 14:40:02 by rbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_map_parsing_info(t_parsing *parsing_info)
{
	t_fill_map	fill_map_info;
	int			return_value;

	init_fill_map(&fill_map_info, parsing_info);
	return_value = read_map(&fill_map_info);
	if (return_value == 1)
		return (1);
	return_value = final_check(&fill_map_info);
	return (return_value);
}

int	fill_config_parsing_info(t_parsing *parsing_info, char *line)
{
	line = get_next_line(parsing_info->fd, 0);
	while (line != NULL && parsing_info->error_code == OK)
	{
		if (parsing_info->col_ok != 1 || parsing_info->text_ok != 1)
		{
			if (empty_line_spaces(line, parsing_info) == 1)
			{
				free(line);
				line = get_next_line(parsing_info->fd, 0);
				continue ;
			}
			if (input_data__not_map(line, parsing_info) == 1)
			{
				free(line);
				return (1);
			}
		}
		free(line);
		if (parsing_info->col_ok == 1 && parsing_info->text_ok == 1)
			return (0);
		line = get_next_line(parsing_info->fd, 0);
	}
	if (line)
		free_null_args(&line);
	return (1);
}

int	parse_arguments_2(int file_lenght, char **file_format)
{
	if (file_lenght < 5)
	{
		print_error(ERROR_WRONG_FORMAT);
		free(*file_format);
		*file_format = NULL;
		return (1);
	}
	return (0);
}

int	parse_arguments(int argc, char **argv, t_parsing *parsing_info)
{
	int		file_lenght;
	char	*file_format;

	if (argc != 2)
		print_error(ERROR_MISSING_CUB);
	if (argc != 2)
		return (1);
	file_lenght = ft_strlen(argv[1]);
	file_format = ft_substr(argv[1], (file_lenght -4), 4);
	if (!file_format)
		print_error(ERROR_MALLOC_1);
	if (!file_format)
		return (1);
	if (ft_strncmp(file_format, ".cub", 4) != 0)
	{
		free_null_args(&file_format);
		print_error(ERROR_WRONG_FORMAT);
		return (1);
	}
	if (parse_arguments_2(file_lenght, &file_format) == 1)
		return (1);
	free(file_format);
	return (check_cub_file(argv, parsing_info));
}

int	parsing(int argc, char **argv, t_parsing *parsing_info)
{
	char	**line;

	line = NULL;
	if (parsing_line_malloc(&line) == 1)
		return (1);
	init_parsing(parsing_info);
	if (parse_arguments(argc, argv, parsing_info) == 1)
	{
		parsing_line_free(line);
		line = NULL;
		return (1);
	}
	if (fill_config_parsing_info(parsing_info, line[0]) == 1)
	{
		parsing_line_free(line);
		line = NULL;
		return (2);
	}
	parsing_line_free(line);
	line = NULL;
	if (fill_map_parsing_info(parsing_info) == 1)
		return (3);
	if (check_map_valid(parsing_info) == 1)
		return (4);
	return (0);
}
