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
			x++;
		}
		y++;
	}
}

t_image *get_texture(int flag, t_game *game)
{
	t_image *current_texture;

	game->ray->ray_ngl = nor_angle(game->ray->ray_ngl);
	if (flag == 0)
	{
		if (game->ray->ray_ngl > PI / 2 && game->ray->ray_ngl < 3 * (PI / 2))
			current_texture = game->textures->WE;
		else
			current_texture = game->textures->EA;

	}
	else
	{
		if (game->ray->ray_ngl > 0 && game->ray->ray_ngl < PI)
			current_texture = game->textures->SO;
		else
			current_texture = game->textures->NO;
	}
	return (current_texture);
}

int get_texture_color(int x, int y, int flag, t_game *game)
{
    t_image *texture = get_texture(flag, game);

    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
        return 0;

    int pixel_index = (y * texture->size_line) + (x * (texture->bpp / 8));

    return *(int *)(texture->data + pixel_index);
}

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	if (x < 0)
		return ;
	else if (x >= WIN_WIDTH)
		return ;
	if (y < 0)
		return ;
	else if (y >= WIN_HEIGHT)
		return ;
	put_pixel(x, y, color, game);
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
	int		c;
	(void)c;
	i = b_pix;
	while (i < WIN_HEIGHT)
		put_pixel(ray, i++, game->F_COLOR, game);
	i = 0;
	while (i < t_pix)
		put_pixel(ray, i++, game->C_COLOR, game);
}

void draw_wall(t_game *game, int ray, int t_pix, int b_pix) // draw the wall
{
    const int wall_height = b_pix - t_pix;
    int tex_x;
    double wall_x;

    if (game->ray->flag == 0) //  (wall intersection position (fractional, normalized to [0, 1])) // vertical wall
        wall_x = fmod(game->ray->vert_y, TILE_SIZE) / TILE_SIZE;
    else // horizontal wall
        wall_x = fmod(game->ray->horiz_x, TILE_SIZE) / TILE_SIZE;

    t_image *texture = get_texture(game->ray->flag, game);
    tex_x = (int)(wall_x * texture->width); // scale to match texture width

	//if (tex_x >= WIN_HEIGHT)
	//	tex_x = WIN_HEIGHT;
	//printf("a: %d\n", b_pix);

    while (t_pix < b_pix)
    {
        int tex_y = (int)((t_pix - (WIN_HEIGHT / 2 - wall_height / 2)) * texture->height / wall_height); // calculate tex_y dynamically to map the texture height to wall height
		if (tex_y >= WIN_HEIGHT)
			tex_y = WIN_HEIGHT;
        int color = get_texture_color(tex_x, tex_y, game->ray->flag, game);
        //my_mlx_pixel_put(game, ray, t_pix++, color);
		put_pixel(ray, t_pix++, color, game);
    }
}

void	render_wall(t_game *game, int ray)	// render the wall
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	game->ray->distance *= cos(nor_angle(game->ray->ray_ngl - game->player->angle)); // fix the fisheye
	wall_h = (TILE_SIZE / game->ray->distance) * ((WIN_WIDTH / 2) / tan(game->player->fov_rd / 2)); // get the wall height
	b_pix = (WIN_HEIGHT / 2) + (wall_h / 2); // get the bottom pixel
	t_pix = (WIN_HEIGHT / 2) - (wall_h / 2); // get the top pixel
	if (b_pix > WIN_HEIGHT) // check the bottom pixel
		b_pix = WIN_HEIGHT;
	if (t_pix <= 0) // check the top pixel
		t_pix = (WIN_HEIGHT) - (wall_h);
	draw_wall(game, ray, t_pix, b_pix); // draw the wall
	draw_floor_ceiling(game, ray, t_pix, b_pix); // draw the floor and the ceiling
}

int	draw_loop(t_game *game)
{
	move_player(game, game->player);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx_pointer, game->mlx_window, game->mlx_image->image, 0, 0);

	mlx_string_put(game->mlx_pointer, game->mlx_window, 10, 20, 0x00FF00, ft_strjoin("Position X: ", ft_itoa(game->player->pos_x)));
	mlx_string_put(game->mlx_pointer, game->mlx_window, 10, 35, 0x00FF00, ft_strjoin("Position Y: ", ft_itoa(game->player->pos_y)));
	mlx_string_put(game->mlx_pointer, game->mlx_window, 10, 50, 0x00FF00, ft_strjoin("Angle Rotation: ", ft_itoa(game->player->angle * (180.0f / PI))));
	if (game->player->touching_wall)
		mlx_string_put(game->mlx_pointer, game->mlx_window, 10, 65, 0x00FF00, "Touching Wall: true");
	else
		mlx_string_put(game->mlx_pointer, game->mlx_window, 10, 65, 0x00FF00, "Touching Wall: false");
	mlx_string_put(game->mlx_pointer, game->mlx_window, 10, 80, 0x00FF00, ft_strjoin("Shortest Distance: ", ft_itoa(game->player->shortest_distance)));
	mlx_string_put(game->mlx_pointer, game->mlx_window, 10, 95, 0x00FF00, ft_strjoin("Test: ", ft_itoa(game->player->test)));
	//init_minimap(game);

	return (0);
}
