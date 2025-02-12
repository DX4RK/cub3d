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
	{
		//printf("Malloc failed extract texture\n");
		return (NULL);
	}
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

int	verif_texture(char *line, t_parsing *parsing_info, int texture_type)
{
	int		i;
	char	*path;

	i = 2;
	if ((texture_type == NO_NUMBER && parsing_info->NO_TEXTURE != NULL)
	 || (texture_type == SO_NUMBER && parsing_info->SO_TEXTURE != NULL)
	 || (texture_type == WE_NUMBER && parsing_info->WE_TEXTURE != NULL)
	 || (texture_type == EA_NUMBER && parsing_info->EA_TEXTURE != NULL))
	{
		parsing_info->error_code = M_T_I_M;
		free(line);
		return (1);
	}
	path = extract_texture_path(line, &i);
	if (!path)
	{
		parsing_info->error_code = M_T_I_M;
		free(line);
		return (1);
	}

	if (check_xpm_extension(path) != 0)
	{
		parsing_info->error_code = M_T_I_M;//mauvaise extension
		free(path);
		free(line);
		return (1);
	}

	skip_spaces(line, &i);
	if (line[i] != '\0' && line[i] != '\n')
	{
		parsing_info->error_code = M_T_I_M;
		free(path);
		free(line);
		return (1);
	}
	if (check_texture_file_valid(path) != 0)
	{
		parsing_info->error_code = M_T_I_M;
		free(path);
		free(line);
		return (1);
	}
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
		parsing_info->texter_info_ok = 1;
	}
	free(line);
	return (0);
}
