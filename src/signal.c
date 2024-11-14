/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:41:03 by noldiane          #+#    #+#             */
/*   Updated: 2024/11/14 13:14:55 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_pressed(int	key_code, t_game *game)
{
	printf("key_pressed: %d\n", key_code);
	if (key_code == QUIT_KEY || key_code == ESC_KEY)
		stop_game(game);
	return (0);
}