#include "cub3d.h"

int	verify_cell_and_neighbors(t_parsing *parsing_info,
	int y, int x, int line_len)
{
	char	c;

	c = parsing_info->map[y][x];
	if (c == ' ')
		return check_space_rules(parsing_info, y, x);
	else if (c == '0')
		return check_floor_rules(parsing_info, y, x, line_len);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return check_player_rules(parsing_info, y, x, line_len);
	return (0);
}

int	check_map_valid(t_parsing *parsing_info)
{
	int	y;
	int	nb_y;

	y = 0;
	nb_y = 0;
	while (parsing_info->map && parsing_info->map[nb_y])
		nb_y++;
	while (y < nb_y)
	{
		if (check_map_line_valid(parsing_info, y, nb_y) == 1)
			return (1);
		y++;
	}
	return (0);
}
