/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:45:18 by noldiane          #+#    #+#             */
/*   Updated: 2025/02/15 14:59:13 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image	*get_texture(int flag, t_game *game)
{
	t_image	*current_texture;

	game->ray->ray_ngl = nor_angle(game->ray->ray_ngl);
	if (flag == 0)
	{
		if (game->ray->ray_ngl > PI / 2 && game->ray->ray_ngl < 3 * (PI / 2))
			current_texture = game->textures->SO;
		else
			current_texture = game->textures->NO;
	}
	else
	{
		if (game->ray->ray_ngl > 0 && game->ray->ray_ngl < PI)
			current_texture = game->textures->EA;
		else
			current_texture = game->textures->WE;
	}
	return (current_texture);
}

void	draw_wall(t_game *game, int ray, int t_pix, int b_pix)
{
	int				tex_x;
	int				tex_y;
	double			wall_x;
	const int		wall_height = b_pix - t_pix;
	const t_image	*texture = get_texture(game->ray->flag, game);

	if (game->ray->flag == 0)
		wall_x = fmod(game->ray->vert_y, TILE_SIZE) / TILE_SIZE;
	else
		wall_x = fmod(game->ray->horiz_x, TILE_SIZE) / TILE_SIZE;
	tex_x = (int)(wall_x * texture->width);
	while (t_pix < b_pix)
	{
		tex_y = (int)((t_pix - (WIN_HEIGHT / 2 - wall_height / 2)) \
		* texture->height / wall_height);
		if (tex_y >= WIN_HEIGHT)
			tex_y = WIN_HEIGHT;
		put_pixel(ray, t_pix++, get_wall_color(game, tex_x, tex_y), game);
	}
}

void	render_wall(t_game *game, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	game->ray->distance *= cos(nor_angle(game->ray->ray_ngl \
		- game->player->angle));
	wall_h = (TILE_SIZE / game->ray->distance) * ((WIN_WIDTH / 2) \
	/ tan(game->player->fov_rd / 2));
	b_pix = (WIN_HEIGHT / 2) + (wall_h / 2);
	t_pix = (WIN_HEIGHT / 2) - (wall_h / 2);
	if (b_pix > WIN_HEIGHT)
		b_pix = WIN_HEIGHT;
	if (t_pix <= 0)
		t_pix = (WIN_HEIGHT) - (wall_h);
	draw_wall(game, ray, t_pix, b_pix);
	draw_floor_ceiling(game, ray, t_pix, b_pix);
}

int	draw_loop(t_game *game)
{
	update_player(game, game->player);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx_pointer, game->mlx_window, \
		game->mlx_image->image, 0, 0);
	return (0);
}
