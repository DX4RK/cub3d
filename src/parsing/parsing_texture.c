/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbauer <rbauer@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 15:58:53 by rbauer            #+#    #+#             */
/*   Updated: 2025/02/20 15:23:09 by rbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*extract_texture_path(char *line, int *i)
{
	int		start;
	int		len;
	char	*path;

	skip_spaces(line, i);
	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '\n')
		(*i)++;
	len = *i - start;
	if (len <= 0)
		return (NULL);
	path = (char *)malloc(sizeof(char) * (len + 1));
	if (!path)
		return (NULL);
	ft_strlcpy(path, &line[start], len + 1);
	return (path);
}

int	check_texture_file_valid(char *path)
{
	int	fd;
	int	return_value;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		return (1);
	}
	return_value = read(fd, 0, 0);
	if (return_value < 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	check_path(char *line, char *path, t_parsing *parsing_info)
{
	(void)line;
	if (!path)
	{
		parsing_info->error_code = M_T_I_M;
		return (1);
	}
	if (check_xpm_extension(path) != 0)
	{
		parsing_info->error_code = M_T_I_M;
		free(path);
		return (1);
	}
	return (0);
}

int	check_texture(char *line, char *path, int i, t_parsing *parsing_info)
{
	if (line[i] != '\0' && line[i] != '\n')
	{
		parsing_info->error_code = M_T_I_M;
		free(path);
		return (1);
	}
	if (check_texture_file_valid(path) != 0)
	{
		parsing_info->error_code = M_T_I_M;
		free(path);
		return (1);
	}
	return (0);
}

int	verif_texture(char *line, t_parsing *parsing_info, int texture_type)
{
	int		i;
	char	*path;

	i = 2;
	if ((texture_type == NO_NUMBER && parsing_info->no_texture != NULL)
		|| (texture_type == SO_NUMBER && parsing_info->so_texture != NULL)
		|| (texture_type == WE_NUMBER && parsing_info->we_texture != NULL)
		|| (texture_type == EA_NUMBER && parsing_info->ea_texture != NULL))
	{
		parsing_info->error_code = M_T_I_M;
		return (1);
	}
	path = extract_texture_path(line, &i);
	if (check_path(line, path, parsing_info))
		return (1);
	skip_spaces(line, &i);
	if (check_texture(line, path, i, parsing_info))
		return (1);
	set_texture(path, parsing_info, texture_type);
	return (0);
}
