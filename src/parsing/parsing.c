/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:34:44 by noldiane          #+#    #+#             */
/*   Updated: 2025/02/18 12:50:07 by noldiane         ###   ########.fr       */
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
	//int	return_value;

	//return_value = 0;
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
	if (check_map_line(fill_map_info->line, fill_map_info->parsing, fill_map_info->y) == 1)
	{
		free(fill_map_info->line);
		return (1);
	}
	if (add_map_line(fill_map_info->parsing, fill_map_info->line) == 1)
	{
		free(fill_map_info->line);
		return (1);
	}
	free(fill_map_info->line);
	fill_map_info->y++;
	return (0);
}

int	read_map(t_fill_map *fill_map_info)
{
	int	return_value;

	return_value = 0;
	while (1)
	{
		fill_map_info->line = get_next_line(fill_map_info->parsing->fd, 0);
		if (fill_map_info->line == NULL || fill_map_info->parsing->error_code != OK)
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



/*
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
		data = check_line1(&line, data, parsing_info);
		if (data.return_value == 2)
			continue ;
		else if (data.return_value == 1)
			break ;
		else
		{
			data = check_line2(&line, &y, data, parsing_info);
			if (data.return_value == 1)
			{
				free_null_args(&line);
				return (1);
			}
		}
		free_null_args(&line);
		line = get_next_line(parsing_info->fd, 0);
	}
	if (line)
		free_null_args(&line);
	if (check_line3(data, parsing_info) == 1)
		return (1);
	return (0);
}
*/

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

int	parsing_line_malloc(char ***line)
{
	*line = malloc(sizeof(char *) * 1);
	if (!*line)
	{
		print_error(ERROR_MALLOC_1);
		return (1);
	}
	*line[0] = NULL;
	return (0);
}

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

int	parsing(int argc, char **argv, t_parsing *parsing_info)
{
	char	**line;

	line = NULL;
	if (parsing_line_malloc(&line) == 1)
		return (1);
	init_parsing(parsing_info);
	if (parse_arguments(argc, argv, parsing_info) == 1)
		return (1);
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
