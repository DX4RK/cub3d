/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:03:51 by noldiane          #+#    #+#             */
/*   Updated: 2024/11/14 11:41:53 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_min(int value1, int value2)
{
	if (value1 > value2)
		return (value2);
	return (value1);
}

int rgb_to_int(int r, int g, int b)
{
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int	get_rgb_value(char *str, int rgb_index)
{
	int	i;
	int	number_len;
	int	comma_count;
	char	*value;

	i = 0;
	number_len = 0;
	comma_count = 0;
	while (str[i])
	{	if (str[i] == ',')

			{
			comma_count++;
			if (comma_count == rgb_index)
				break;
			number_len = 0;
		}
		else
			number_len++;
		i++;
	}
	value = ft_substr(str, i - number_len, number_len);
	i = ft_atoi(value);
	free(value);
	return (i);
}

int	str_to_hex(char *str)
{
	int	hex_color;
	hex_color = rgb_to_int(get_rgb_value(str, 1) , \
	get_rgb_value(str, 2) , \
	get_rgb_value(str, 3) );
	return (hex_color);
}

void	print_error(char *str)
{
	printf(RED BOLD "[ERROR] ");
	printf(RESET);
	if (str)
		printf("%s\n", str);
}

void	print_title()
{
	printf(RED "\n");
	printf("\t ██████ ██    ██ ██████  ██████  ██████  \n");
	printf("\t██      ██    ██ ██   ██      ██ ██   ██ \n");
	printf("\t██      ██    ██ ██████   █████  ██   ██ \n");
	printf("\t██      ██    ██ ██   ██      ██ ██   ██ \n");
	printf("\t ██████  ██████  ██████  ██████  ██████  \n");  
	printf(RESET "\n");   
}

void	print_keys()
{
	printf(LIGHT_ORANGE BOLD "\t  [W]" RESET "-> avancer\t");
	printf(LIGHT_ORANGE BOLD "\t  [S]" RESET "-> reculer\n");
	printf(LIGHT_ORANGE BOLD "\t  [A]" RESET "-> gauche\t");
	printf(LIGHT_ORANGE BOLD "\t  [D]" RESET "-> droite\n");
	printf(ITAL "\n\t\ttouches des mouvement\n");
	printf(RESET "\n");
}