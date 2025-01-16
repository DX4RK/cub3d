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

	new_x = player->x;
	new_y = player->y;

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
		player->x = new_x;
		player->y = new_y;
	//}
}
*/

void	move_player(t_game *game, t_player *player)
{
	const float angle_speed = 0.01f;
	const float move_speed = 2.0f;

	int new_x = player->x;
	int new_y = player->y;

	float pdx, pdy;

	if (player->rotate_left)
	{
		player->angle -= angle_speed;
		if (player->angle < 0)
			player->angle += 2 * PI;
	}

	if (player->rotate_right)
	{
		player->angle += angle_speed;
		if (player->angle >= 2 * PI)
			player->angle -= 2 * PI;
	}

	pdx = cos(player->angle) * move_speed;
	pdy = sin(player->angle) * move_speed;

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
		new_x -= pdy;
		new_y += pdx;
	}

	if (player->key_right)
	{
		new_x += pdy;
		new_y -= pdx;
	}

	if (touch(new_x, new_y, game))
		player->touching_wall = true;
	else if (new_x != player->x || new_y != player->y)
	{
		player->x = new_x;
		player->y = new_y;
		player->touching_wall = false;
	}
}
