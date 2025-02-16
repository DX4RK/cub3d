/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:41:03 by noldiane          #+#    #+#             */
/*   Updated: 2025/02/14 14:45:07 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key_code, t_game *game)
{
	if (key_code == QUIT_KEY || key_code == ESC_KEY)
		stop_game(game);
	if (key_code == FORWARD_KEY)
		game->player->key_up = true;
	if (key_code == BACK_KEY)
		game->player->key_down = true;
	if (key_code == LEFT_KEY)
		game->player->key_left = true;
	if (key_code == RIGHT_KEY)
		game->player->key_right = true;
	if (key_code == LEFT_ARROW)
		game->player->rotate_left = true;
	if (key_code == RIGHT_ARROW)
		game->player->rotate_right = true;
	return (0);
}

int	key_release(int key_code, t_game *game)
{
	if (key_code == FORWARD_KEY)
		game->player->key_up = false;
	if (key_code == BACK_KEY)
		game->player->key_down = false;
	if (key_code == LEFT_KEY)
		game->player->key_left = false;
	if (key_code == RIGHT_KEY)
		game->player->key_right = false;
	if (key_code == LEFT_ARROW)
		game->player->rotate_left = false;
	if (key_code == RIGHT_ARROW)
		game->player->rotate_right = false;
	return (0);
}
