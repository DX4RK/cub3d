#include "cub3d.h"

int	line_is_empty(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	add_map_line(t_parsing *parsing_info, char *str)
{
	int		i;
	int		count;
	char	**new_map;

	count = 0;
	if (parsing_info->map)
	{
		while (parsing_info->map[count])
			count++;
	}
	new_map = malloc(sizeof(char *) * (count + 1 + 1));
	if (!new_map)
	{
		//error
		return (1);
	}
	i = 0;
	while (i < count)
	{
		new_map[i] = parsing_info->map[i];
		i++;
	}
	new_map[count] = ft_strdup(str);
	if (!new_map[count])
	{
		//malloc error handeled in strdup ?
		free(new_map);
		return (1);
	}
	new_map[count + 1] = NULL;
	if (parsing_info->map)
		free(parsing_info->map);
	parsing_info->map = new_map;
	return (0);
}

int	check_map_line(char *line, t_parsing *parsing_info, int y)
{
	int i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
		{
			if (parsing_info->player_set != -1)
			{
				parsing_info->error_code = P_A_S;
				return (1);
			}
			parsing_info->player_set = 1;
			parsing_info->player_y = y;
			parsing_info->player_x = i;
			parsing_info->player_letter = line[i];
		}
		else if (line[i] != ' ' && line[i] != '1' && line[i] != '0')
		{
			parsing_info->error_code = I_C;
			return (1);
		}
		i++;
	}
	return (0);
}

int	test_end_map_lines(t_parsing *parsing_info)
{
	char	*line;

	while ((line = get_next_line(parsing_info->fd, 0)) != NULL)
	{
		if (!line_is_empty(line))
		{
			parsing_info->error_code = M_N_C;
			free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}
