#include "cub3d.h"

void	move_player(t_game *game, t_player *player)
{
	const int	speed = 1;
	float		angle_speed = 0.01;
	float		cos_angle = cos(player->angle);
	float		sin_angle = sin(player->angle);

	int			new_x;
	int			new_y;

	new_x = player->x;
	new_y = player->y;
	if (player->rotate_left)
		player->angle -= angle_speed;
	if (player->rotate_right)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;

	if (player->key_up)
	{
		new_x += cos_angle * speed;
		new_y += sin_angle * speed;
	}
	if (player->key_down)
	{
		new_x -= cos_angle * speed;
		new_y -= sin_angle * speed;
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

	if (!touch(new_x, new_y, game))
	{
		player->x = new_x;
		player->y = new_y;
	}
}
