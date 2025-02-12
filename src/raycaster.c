#include "cub3d.h"

int	unit_circle(float angle, char c)	// check the unit circle
{
	if (c == 'x')
	{
		if (angle > 0 && angle < PI)
			return (1);
	}
	else if (c == 'y')
	{
		if (angle > (PI / 2) && angle < (3 * PI) / 2)
			return (1);
	}
	return (0);
}

int	inter_check(float angle, float *inter, float *step, int is_horizon)	// check the intersection
{
	if (is_horizon)
	{
		if (angle > 0 && angle < PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > PI / 2 && angle < 3 * PI / 2))
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	wall_hit(float x, float y, t_game *game)	// check the wall hit
{
	int		x_m;
	int		y_m;

	if (x < 0 || y < 0)
		return (0);
	x_m = floor (x / TILE_SIZE);
	y_m = floor (y / TILE_SIZE);
	if ((y_m >= game->map_height || x_m >= 15))
		return (0);
	if (game->map[y_m] && x_m <= (int)strlen(game->map[y_m]))
		if (game->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

float	get_h_inter(t_game *game, float angl)	// get the horizontal intersection
{
	float	h_x;
	float	h_y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	h_y = floor(game->player->pos_y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = game->player->pos_x + (h_y - game->player->pos_y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') && x_step < 0)) // check x_step value
		x_step *= -1;
	while (wall_hit(h_x, h_y - pixel, game)) // check the wall hit whit the pixel value
	{
		h_x += x_step;
		h_y += y_step;
	}
	game->ray->horiz_x = h_x;
	game->ray->horiz_y = h_y;
	return (sqrt(pow(h_x - game->player->pos_x, 2) + pow(h_y - game->player->pos_y, 2))); // get the distance
}

float	get_v_inter(t_game *game, float angl)	// get the vertical intersection
{
	float	v_x;
	float	v_y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angl);
	v_x = floor(game->player->pos_x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &v_x, &x_step, 0); // check the intersection and get the pixel value
	v_y = game->player->pos_y + (v_x - game->player->pos_x) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0) || (!unit_circle(angl, 'x') && y_step > 0)) // check y_step value
		y_step *= -1;
	while (wall_hit(v_x - pixel, v_y, game)) // check the wall hit whit the pixel value
	{
		v_x += x_step;
		v_y += y_step;
	}
	game->ray->vert_x = v_x;
	game->ray->vert_y = v_y;
	return (sqrt(pow(v_x - game->player->pos_x, 2) + pow(v_y - game->player->pos_y, 2))); // get the distance
}

bool	touch(float px, float py, t_game *game)
{
	int x = px / TILE_SIZE;
	int y = py / TILE_SIZE;
	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

int test_text(int flag, t_game *game)
{
	int current_texture;

	double angl = nor_angle(game->player->angle);
	if (flag == 0)
	{
		if (angl > PI / 2 && angl < 3 * (PI / 2))
			current_texture = 1;
		else
			current_texture = 2;

	}
	else
	{
		if (game->ray->ray_ngl > 0 && game->ray->ray_ngl < PI)
			current_texture = 3;
		else
			current_texture = 4;
	}
	return (current_texture);
}

void	cast_rays(t_game *game)	// cast the rays
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	game->player->shortest_distance = 1000;
	game->ray->ray_ngl = game->player->angle - (game->player->fov_rd / 2); // the start angle
	while (ray < WIN_WIDTH) // loop for the rays
	{
		game->ray->flag = 0; // flag for the wall
		h_inter = get_h_inter(game, nor_angle(game->ray->ray_ngl)); // get the horizontal intersection
		v_inter = get_v_inter(game, nor_angle(game->ray->ray_ngl)); // get the vertical intersection
		if (v_inter <= h_inter) // check the distance
			game->ray->distance = v_inter; // get the distance
		else
		{
			game->ray->distance = h_inter; // get the distance
			game->ray->flag = 1; // flag for the wall
		}
		if (game->ray->distance < game->player->shortest_distance)
			game->player->shortest_distance = game->ray->distance;
		//if (ray == 0)
		//{
		//	game->player->test = test_text(game->ray->flag, game);
		//}
		render_wall(game, ray); // render the wall
		ray++; // next ray
		game->ray->ray_ngl += (game->player->fov_rd / WIN_WIDTH); // next angle
	}
}
