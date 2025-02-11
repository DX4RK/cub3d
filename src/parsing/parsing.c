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
/*
int	parse_arguments(int argc, char *argv[])
{
	int		fd;
	int		file_lenght;
	char	*file_format;

	if (argc != 2)
	{
		print_error(ERROR_MISSING_CUB);
		exit(EXIT_SUCCESS);
	}
	file_lenght = ft_strlen(argv[1]);
	file_format = ft_substr(argv[1], (file_lenght -4), 4);
	if (ft_strncmp(file_format, ".cub", 4) != 0)
	{
		free(file_format);
		print_error(ERROR_WRONG_FORMAT);
		exit(EXIT_SUCCESS);
	}
	free(file_format);
	fd = open(argv[1], O_RDONLY);
	if (read(fd, 0, 0) != 0)
	{
		print_error(FILE_NOT_EXIST);
		exit(EXIT_SUCCESS);
	}
	return (fd);
}
*/
