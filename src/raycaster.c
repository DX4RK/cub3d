#include "cub3d.h"

float	distance(float x, float y)
{
	return sqrt(x * x + y * y);
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float	delta_x = x2 - x1;
	float	delta_y = y2 - y1;
	float	angle = atan2(delta_y, delta_x) - game->player->angle;
	float	fix_dist = distance(delta_x, delta_y) * cos(angle);

	return (fix_dist);
}

bool	touch(float px, float py, t_game *game)
{
	int x = px / 64;
	int y = py / 64;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}
