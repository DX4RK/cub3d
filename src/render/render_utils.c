/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbauer <rbauer@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:04:15 by noldiane          #+#    #+#             */
/*   Updated: 2025/02/20 15:22:30 by rbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = game->mlx_image->data + (y * game->mlx_image->size_line \
		+ x * (game->mlx_image->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_texture_color(int x, int y, int flag, t_game *game)
{
	const t_image	*texture = get_texture(flag, game);
	const int		pixel_index = (y * texture->size_line) \
	+ (x * (texture->bpp / 8));

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	return (*(int *)(texture->data + pixel_index));
}

int	get_wall_color(t_game *game, int tex_x, int tex_y)
{
	int	wall_color;

	wall_color = get_texture_color(tex_x, tex_y, game->ray->flag, game);
	return (wall_color);
}

float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * PI);
	if (angle > (2 * PI))
		angle -= (2 * PI);
	return (angle);
}

void	draw_floor_ceiling(t_game *game, int ray, int t_pix, int b_pix)
{
	int		i;

	i = b_pix;
	while (i < WIN_HEIGHT)
		put_pixel(ray, i++, game->f_color, game);
	i = 0;
	while (i < t_pix)
		put_pixel(ray, i++, game->c_color, game);
}
