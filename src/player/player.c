#include "cub3d.h"

/*
void	move_player(t_game *game, t_player *player)
{
	//const int			speed = 2;
	const float		angle_speed = 0.01;

	int			new_x;
	int			new_y;

	float			pdx;
	float			pdy;

	new_x = player->pos_x;
	new_y = player->pos_y;

	if (player->rotate_left)
	{
		player->angle -= angle_speed;
		if (player->angle < 0)
			player->angle += 2 * PI;
	}

	if (player->rotate_right)
	{
		player->angle += angle_speed;
		if (player->angle < 0)
			player->angle -= 2 * PI;
	}

	pdx = cos(player->angle) * 2;
	pdy = sin(player->angle) * 2;

	if (player->key_up)
	{
		new_x += pdx;
		new_y += pdy;
	}
	if (player->key_down)
	{
		new_x -= pdx;
		new_y -= pdy;
	}

	if (player->key_left)
	{
		new_x += cos_angle * speed;
		new_y -= sin_angle * speed;
	}
	if (player->key_right)
	{
		new_x -= cos_angle * speed;
		new_y += sin_angle * speed;
	}

	(void)game;
	//if (!touch(new_x, new_y, game))
	//{
		player->pos_x = new_x;
		player->pos_y = new_y;
	//}
}
*/

void	move_player(t_game *game, t_player *player)
{
	double	new_x;
	double	new_y;
	double	rotate_speed;

	new_x = player->pos_x;
	new_y = player->pos_y;
	if (player->key_up)
	{
		new_x = game->player->pos_x + player->dir_x * MOVE_SPEED;
		new_y = game->player->pos_y + player->dir_y * MOVE_SPEED;
	}
	else if (player->key_down)
	{
		new_x = game->player->pos_x - player->dir_x * MOVE_SPEED;
		new_y = game->player->pos_y - player->dir_y * MOVE_SPEED;
	}
	if (player->key_left)
	{
		new_x = game->player->pos_x + player->dir_y * MOVE_SPEED;
		new_y = game->player->pos_y - player->dir_x * MOVE_SPEED;
	}
	else if (player->key_right)
	{
		new_x = game->player->pos_x - player->dir_y * MOVE_SPEED;
		new_y = game->player->pos_y + player->dir_x * MOVE_SPEED;
	}
	if (player->rotate_left)
		rotate_speed = ROTATE_SPEED * -1;
	else if (player->rotate_right)
		rotate_speed = ROTATE_SPEED * 1;
	if (player->rotate_left || player->rotate_right)
	{
		double	tmp_x = player->dir_x;
		player->dir_x = player->dir_x * cos(rotate_speed) - player->dir_y * sin(rotate_speed);
		player->dir_y = tmp_x * sin(rotate_speed) + player->dir_y * cos(rotate_speed);

		tmp_x = player->plane_x;
		player->plane_x = player->plane_x * cos(rotate_speed) - player->plane_y * sin(rotate_speed);
		player->plane_y = tmp_x * sin(rotate_speed) + player->plane_y * cos(rotate_speed);
	}

	if (touch(new_x, new_y, game) || (player->shortest_distance <= (FOV / 2.5) && !player->key_down))
		player->touching_wall = true;
	else if ((player->pos_x != new_x) || (player->pos_y != new_y))
	{
		player->touching_wall = false;
		player->pos_x = new_x;
		player->pos_y = new_y;
	}
	player->angle = atan2(player->dir_y, player->dir_x);
}
//|| (player->shortest_distance <= (FOV / 2) && !player->key_down)
