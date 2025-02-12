#include "cub3d.h"

int	input_data__NOT_MAP(char *line, t_parsing *parsing_info)
{
	if (line[0] == 'F' && line[1] == ' ')
	{
		if (verif_color(line, parsing_info, 0) == 1)
		{
			return (1);
		}
		return (0);
	}
	else if (line[0] == 'C' && line[1] == ' ')
	{
		if (verif_color(line, parsing_info, 1) == 1)
			return (1);
		return (0);
	}
	else if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
	{
		if (verif_texture(line, parsing_info, NO_NUMBER) == 1)
			return (1);
		return (0);
	}
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
	{
		if (verif_texture(line, parsing_info, SO_NUMBER) == 1)
			return (1);
		return (0);
	}
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
	{
		if (verif_texture(line, parsing_info, WE_NUMBER) == 1)
			return (1);
		return (0);
	}
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
	{
		if (verif_texture(line, parsing_info, EA_NUMBER) == 1)
			return (1);
		return (0);
	}
	else
	{
		parsing_info->error_code = I_C;
		return (1);
	}
	return (0);
}

int	check_xpm_extension(const char *path)
{
	int	len;

	if (!path)
		return (1);
	len = ft_strlen(path);
	if (len < 5)
		return (1);
	if (ft_strncmp(path + (len - 4), ".xpm", 4) != 0)
		return (1);
	return (0);
}

int	ft_strlen__NO_N(const char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0' && str[index] != '\n')
	{
		index++;
	}
	return (index);
}

char	get_neighbor_char(t_parsing *parsing_info, int y, int x,
	int nb_y)
{
	char	*line;

	if (y < 0 || y >= nb_y)
		return (' ');
	line = parsing_info->map[y];
	if (!line)
		return (' ');
	if (x < 0 || x >= ft_strlen__NO_N(line))
		return (' ');
	return (line[x]);
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
