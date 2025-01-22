#include "cub3d.h"

void	clear_image(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(x, y, 0, game);
			//put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}

void	draw_map(t_game *game)
{
	int	x;
	int	y;
	int	color = 0x0000FF;

	x = 0;
	y = 0;
	while (game->map[y])
	{
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				draw_square(x * 64, y * 64, 64, color, game);
			x++;
		}
		y++;
		x = 0;
	}
}

void	draw_line(t_game *game, float start_x, int i)
{
	(void)i;
	float		ray_x = game->player->pos_x;
	float		ray_y = game->player->pos_y;
	float		cos_angle = cos(start_x);
	float		sin_angle = sin(start_x);

	while (!touch(ray_x, ray_y, game))
	{
		//if (DEBUG)
		put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}

	

}


int	draw_loop(t_game *game)
{
	clear_image(game);
	move_player(game, game->player);

	draw_square(game->player->pos_x, game->player->pos_y, 10, 0x00FF00, game);
	draw_map(game);

	int		i = 0;
	float	fraction = PI / 2 / WIN_WIDTH;
	float	ray_angle = atan2(game->player->dir_y, game->player->dir_x) - (PI / 4);
	//float	start_x = game->player->angle - PI / 4;

	while (i < WIN_WIDTH)
	{
		draw_line(game, ray_angle, i);
		ray_angle += fraction;
		i++;
	}

	mlx_put_image_to_window(game->mlx_pointer, game->mlx_window, game->mlx_image, 0, 0);
	mlx_string_put(game->mlx_pointer, game->mlx_window, 10, 20, 0x00FF00, ft_strjoin("Position X: ", ft_itoa(game->player->pos_x)));
	mlx_string_put(game->mlx_pointer, game->mlx_window, 10, 35, 0x00FF00, ft_strjoin("Position Y: ", ft_itoa(game->player->pos_y)));
	mlx_string_put(game->mlx_pointer, game->mlx_window, 10, 50, 0x00FF00, ft_strjoin("Angle Rotation: ", ft_itoa(game->player->angle * (180.0f / PI))));
	if (game->player->touching_wall)
		mlx_string_put(game->mlx_pointer, game->mlx_window, 10, 65, 0x00FF00, "Touching Wall: true");
	else
		mlx_string_put(game->mlx_pointer, game->mlx_window, 10, 65, 0x00FF00, "Touching Wall: false");
	return (0);
}

/*
float	ray_x = game->player->pos_x;
	float	ray_y = game->player->pos_y;
	float		cos_angle = cos(game->player->angle);
	float		sin_angle = sin(game->player->angle);

	while (!touch(ray_x, ray_y, game))
	{
		put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
*/
