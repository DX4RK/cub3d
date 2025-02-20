/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbauer <rbauer@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:52:26 by noldiane          #+#    #+#             */
/*   Updated: 2025/02/20 14:49:04 by rbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	touch(float px, float py, t_game *game)
{
	const int	x = px / TILE_SIZE;
	const int	y = py / TILE_SIZE;

	if (game->map[y][x] == '1')
		return (true);
	return (false);
}

void	set_player_angle(t_player *player, double angle_degrees)
{
	const double	angle_radians = angle_degrees * (PI / 180.0);
	const double	plane_length = tan(30.0 * (PI / 180.0));

	player->dir_x = cos(angle_radians);
	player->dir_y = sin(angle_radians);
	player->plane_x = -player->dir_y * plane_length;
	player->plane_y = player->dir_x * plane_length;
	player->angle = atan2(player->dir_y, player->dir_x);
}

t_position	move_player(t_game *game, t_player *player)
{
	t_position	new;

	new.x = player->pos_x;
	new.y = player->pos_y;
	if (player->key_up)
	{
		new.x = game->player->pos_x + player->dir_x * MOVE_SPEED;
		new.y = game->player->pos_y + player->dir_y * MOVE_SPEED;
	}
	else if (player->key_down)
	{
		new.x = game->player->pos_x - player->dir_x * MOVE_SPEED;
		new.y = game->player->pos_y - player->dir_y * MOVE_SPEED;
	}
	if (player->key_left)
	{
		new.x = game->player->pos_x + player->dir_y * MOVE_SPEED;
		new.y = game->player->pos_y - player->dir_x * MOVE_SPEED;
	}
	else if (player->key_right)
	{
		new.x = game->player->pos_x - player->dir_y * MOVE_SPEED;
		new.y = game->player->pos_y + player->dir_x * MOVE_SPEED;
	}
	return (new);
}

void	rotate_player(t_player *player)
{
	double	tmp_x;
	double	rotate_speed;

	if (player->rotate_left)
		rotate_speed = ROTATE_SPEED * -1;
	else if (player->rotate_right)
		rotate_speed = ROTATE_SPEED * 1;
	tmp_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rotate_speed) \
	- player->dir_y * sin(rotate_speed);
	player->dir_y = tmp_x * sin(rotate_speed) \
	+ player->dir_y * cos(rotate_speed);
	tmp_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rotate_speed) \
	- player->plane_y * sin(rotate_speed);
	player->plane_y = tmp_x * sin(rotate_speed) \
	+ player->plane_y * cos(rotate_speed);
	player->angle = atan2(player->dir_y, player->dir_x);
}

void	update_player(t_game *game, t_player *player)
{
	t_position	new_position;

	if (player->key_up || player->key_down || \
		player->key_left || player->key_right)
	{
		new_position = move_player(game, player);
		if (touch(new_position.x, new_position.y, game) \
		|| (player->shortest_distance <= (FOV / 2.5) && !player->key_down))
			player->touching_wall = true;
		else if ((player->pos_x != new_position.x) \
		|| (player->pos_y != new_position.y))
		{
			player->touching_wall = false;
			player->pos_x = new_position.x;
			player->pos_y = new_position.y;
		}
	}
	if (player->rotate_left || player->rotate_right)
		rotate_player(player);
}
