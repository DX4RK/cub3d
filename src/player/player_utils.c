/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbauer <rbauer@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:30:45 by rbauer            #+#    #+#             */
/*   Updated: 2025/02/20 14:32:19 by rbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_look(t_game *game, t_parsing *parsing_info)
{
	if (parsing_info->player_letter == 'N')
		set_player_angle(game->player, 0);
	else if (parsing_info->player_letter == 'S')
		set_player_angle(game->player, 180);
	else if (parsing_info->player_letter == 'W')
		set_player_angle(game->player, 270);
	else if (parsing_info->player_letter == 'E')
		set_player_angle(game->player, 90);
}

int	unit_circle(float angle, char c)
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
