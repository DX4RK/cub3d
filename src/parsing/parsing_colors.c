#include "cub3d.h"

int	parse_color_value(char *line, t_parsing *parsing_info, int *i)
{
	int	sign;
	int	color_value;
	int	len;

	sign = 1;
	color_value = -1;
	if (line[*i] == '+' || line[*i] == '-')
	{
		if (line[*i] == '-')
			sign = -1;
		(*i)++;
	}
	len = 0;
	if (ft_isdigit(line[*i]))
		color_value = 0;
	while (ft_isdigit(line[*i]))
	{
		color_value = color_value * 10 + (line[*i] - '0');
		(*i)++;
		len++;
		if (color_value > 255 || len > 3 || sign == -1 || len == 0)
		{
			parsing_info->error_code = M_C_I_M;
			return (-1);
		}
	}
	return (color_value);
}

int	save_color(t_parsing *parsing_info, int color_type)
{
	if (parsing_info->red == -1 || parsing_info->green == -1 || parsing_info->blue == -1)
	{
		parsing_info->error_code = M_C_I_M;
		return (1);
	}
	if (color_type == 0)
		parsing_info->F_COLOR = rgb_to_int(parsing_info->red, parsing_info->green, parsing_info->blue);
	if (color_type == 1)
		parsing_info->C_COLOR = rgb_to_int(parsing_info->red, parsing_info->green, parsing_info->blue);
	parsing_info->red = -1;
	parsing_info->green = -1;
	parsing_info->blue = -1;
	return (0);
}

int	input_color(char *line, t_parsing *parsing_info, int i, int color_type)
{
	skip_spaces(line, &i);
	parsing_info->red = parse_color_value(line, parsing_info, &i);
	skip_spaces(line, &i);
	if (line[i] != ',')
		parsing_info->error_code = M_C_I_M;
	i++;
	skip_spaces(line, &i);
	parsing_info->green = parse_color_value(line, parsing_info, &i);
	skip_spaces(line, &i);
	if (line[i] != ',')
		parsing_info->error_code = M_C_I_M;
	i++;
	skip_spaces(line, &i);
	parsing_info->blue = parse_color_value(line, parsing_info, &i);
	skip_spaces(line, &i);
	if (line[i] != '\0' && line[i] != '\n')
		parsing_info->error_code = M_C_I_M;
	if (save_color(parsing_info, color_type) == 1)
		return (1);
	return (0);
}

int	verif_color(char *line, t_parsing *parsing_info, int color_type)
{
	int	temp;

	if (color_type == 0)
		temp = parsing_info->F_COLOR;
	else if (color_type == 1)
		temp = parsing_info->C_COLOR;
	if (temp != -1)
	{
		parsing_info->error_code = M_C_I_M;
		free(line);
		line = NULL;
		return (1);
	}
	if (input_color(line, parsing_info, 1, color_type) == 1)
	{
		free(line);
		line = NULL;
		return (1);
	}
	else//pas besoin normalement, peut mettre contenu sans la structure else
	{
		free(line);
		line = NULL;
		if (parsing_info->C_COLOR != -1 && parsing_info->F_COLOR != -1)
			parsing_info->color_info_ok = 1;
	}
	return (0);
}
