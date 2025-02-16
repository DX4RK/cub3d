/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:03:51 by noldiane          #+#    #+#             */
/*   Updated: 2025/02/14 14:49:23 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_min(int value1, int value2)
{
	if (value1 > value2)
		return (value2);
	return (value1);
}

int	rgb_to_int(int r, int g, int b)
{
	int	new_value;

	new_value = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (new_value);
}

void	print_error(char *str)
{
	printf(RED BOLD "[ERROR] ");
	printf(RESET);
	if (str)
		printf("%s\n", str);
}

void	print_title(void)
{
	printf(RED "\n");
	printf("\t ██████ ██    ██ ██████  ██████  ██████  \n");
	printf("\t██      ██    ██ ██   ██      ██ ██   ██ \n");
	printf("\t██      ██    ██ ██████   █████  ██   ██ \n");
	printf("\t██      ██    ██ ██   ██      ██ ██   ██ \n");
	printf("\t ██████  ██████  ██████  ██████  ██████  \n");
	printf(RESET "\n");
}

void	print_keys(void)
{
	printf(LIGHT_ORANGE BOLD "\t  [W]" RESET "-> avancer\t");
	printf(LIGHT_ORANGE BOLD "\t  [S]" RESET "-> reculer\n");
	printf(LIGHT_ORANGE BOLD "\t  [A]" RESET "-> gauche\t");
	printf(LIGHT_ORANGE BOLD "\t  [D]" RESET "-> droite\n");
	printf(ITAL "\n\t\ttouches des mouvement\n");
	printf(RESET "\n");
}
