/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:34:44 by noldiane          #+#    #+#             */
/*   Updated: 2024/11/14 11:39:02 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_map_parsing_info(t_parsing *parsing_info)
{
	char	*line;
	int		started_map;
	int		ended_map;
	int		y;

	started_map = 0;
	ended_map = 0;
	y = 0;
	while ((line = get_next_line(parsing_info->fd, 0)) != NULL && parsing_info->error_code == OK)
	{
		if (line_is_empty(line))
		{
			free(line);
			if (!started_map)
			{
				continue;
			}
			else //fin de map ligne vide
			{
				ended_map = 1;
				if (test_end_map_lines(parsing_info) == 1)
					return (1);
				break;
			}
		}
		else
		{
			if (ended_map)//blabla après fin de carte mais dc carte ouverte pas fermée
			{
				parsing_info->error_code = M_N_C;
				free(line);
				return (1);
			}
			started_map = 1;
			if (check_map_line(line, parsing_info, y) == 1)
			{
				free(line);
				return (1);
			}
			if (add_map_line(parsing_info, line) == 1)
			{
				//malloc error
				free(line);
				return (1);
			}
			free(line);
			y++;
		}
	}
	if (started_map == 0)
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

int	fill_config_parsing_info(t_parsing *parsing_info)
{
	char	*line;

	while ((line = get_next_line(parsing_info->fd, 0)) != NULL && parsing_info->error_code == OK)
	{
		if (parsing_info->color_info_ok != 1 || parsing_info->texter_info_ok != 1)
		{
			if (empty_line_spaces(line, parsing_info) == 1)
				continue ;
			if (input_data__NOT_MAP(line, parsing_info) == 1)
				return (1);
		}
		if (parsing_info->color_info_ok == 1 && parsing_info->texter_info_ok == 1)
			return (0);
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
		printf("\n");
		return (1);
	}
	file_lenght = ft_strlen(argv[1]);
	file_format = ft_substr(argv[1], (file_lenght -4), 4);
	if (!file_format)
	{
		//print_error malloc
		return (1);
	}
	if (ft_strncmp(file_format, ".cub", 4) != 0)
	{
		free(file_format);
		print_error(ERROR_WRONG_FORMAT);
		printf("\n");
		return (1);
	}
	if (file_lenght < 5)
	{
		free(file_format);
		//print_error only extension but not a card name
		return (1);
	}
	free(file_format);
	parsing_info->fd = open(argv[1], O_RDONLY);
	if (read(parsing_info->fd, 0, 0) != 0)//vérif si prend en compte erreur si dossier au lieu de fichier
	{
		print_error(FILE_NOT_EXIST);
		return (1);
	}
	return (0);
}

int	parsing(int argc, char **argv, t_parsing *parsing_info)
{
	init_parsing(parsing_info);
	if (parse_arguments(argc, argv, parsing_info) == 1)
		return (1);//pas de changement du error code fait
	if (fill_config_parsing_info(parsing_info) == 1)
		return (2);
	if (fill_map_parsing_info(parsing_info) == 1)
		return (3);
	if (check_map_valid(parsing_info) == 1)
		return (4);
	return (0);
}
