/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 04:19:39 by redadgh           #+#    #+#             */
/*   Updated: 2025/09/29 15:50:28 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

unsigned int	color_to_int(t_color c)
{

    return ((c.r << 24) | (c.g << 16) | (c.b << 8) | 0xFF);
}

void	draw_floor_and_ceiling(t_game_data *game_data)
{
	int				y;
	int				x;
	unsigned int	ceil_color;
	unsigned int	floor_color;

	ceil_color = color_to_int(game_data->scene->ceiling);
	floor_color = color_to_int(game_data->scene->floor);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(game_data->img, x, y, ceil_color);
			else
				mlx_put_pixel(game_data->img, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void	calculate_ray_direction(double x, t_player *player, 
								t_wall_data *wall_data)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	wall_data->ray_dir_x = player->dir_x + player->plane_x * camera_x;
	wall_data->ray_dir_y = player->dir_y + player->plane_y * camera_x;
	if (wall_data->ray_dir_x == 0.0)
		wall_data->ray_dir_x = 1e-30;
	if (wall_data->ray_dir_y == 0.0)
		wall_data->ray_dir_y = 1e-30;
}

void	calculate_step_and_side_dist(t_player *player, t_wall_data *wall_data, 
									t_dda_data *dda)
{
	dda->map_x = (int)player->pos_x;
	dda->map_y = (int)player->pos_y;
	dda->delta_dist_x = fabs(1 / wall_data->ray_dir_x);
	dda->delta_dist_y = fabs(1 / wall_data->ray_dir_y);
	if (wall_data->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (player->pos_x - dda->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - player->pos_x)
			* dda->delta_dist_x;
	}
	if (wall_data->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (player->pos_y - dda->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - player->pos_y) 
			* dda->delta_dist_y;
	}
}

void	perform_dda(t_scene *scene, t_dda_data *dda)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (dda->map_x < 0 || dda->map_y < 0 || scene->map[dda->map_y] == NULL)
			hit = 1;
		else if (dda->map_x >= (int)ft_strlen(scene->map[dda->map_y]))
			hit = 1;
		else if (scene->map[dda->map_y][dda->map_x] == '1')
			hit = 1;
		else if (scene->map[dda->map_y][dda->map_x] == 'D')
		{
			// double dx = player->pos_x - (dda->map_x + 0.5);
			// double dy = player->pos_y - (dda->map_y + 0.5);
			// double dist = sqrt(dx * dx + dy * dy);

		// if (dist < 1.5)
		// 	hit = 0;
		// else
			hit = 1;
		}
	}
}
void	interact_with_door(t_scene *scene, t_player *player, mlx_t *mlx)
{
	double	dir_x = player->dir_x;
	double	dir_y = player->dir_y;
	int		check_x = (int)(player->pos_x + dir_x);
	int		check_y = (int)(player->pos_y + dir_y);
	int		y =-1;
	int		x =-1;

	if (mlx_is_key_down(mlx, MLX_KEY_E))
	{
		if (check_x < 0 || check_y < 0 || scene->map[check_y] == NULL)
			return;
		if (check_x >= (int)ft_strlen(scene->map[check_y]))
			return;

		if (scene->map[check_y][check_x] == 'D')
		{
			// Optional: check distance before allowing
			double dx = player->pos_x - (check_x + 0.5);
			double dy = player->pos_y - (check_y + 0.5);
			double dist = sqrt(dx * dx + dy * dy);

			if (dist < 1.5)
			{
				scene->map[check_y][check_x] = 'o'; // Open the door
				// Optional: play sound or animation here
			}
		}
	}
	else
		while (scene->map[++y] != NULL)
			while (x < (int)ft_strlen(scene->map[y]))
				if (scene->map[y][x] == 'o')
					scene->map[y][x] = 'D';
}

void	calculate_wall_distance(t_player *player, t_wall_data *wall_data,
								t_dda_data *dda)
{
	if (dda->side == 0)
		dda->perp_wall_dist = (dda->map_x - player->pos_x 
				+ (1 - dda->step_x) / 2) / wall_data->ray_dir_x;
	else
		dda->perp_wall_dist = (dda->map_y - player->pos_y 
				+ (1 - dda->step_y) / 2) / wall_data->ray_dir_y;
}

void	calculate_draw_bounds(double perp_wall_dist, int *draw_start, 
							int *draw_end, int *line_height)
{
	*line_height = (int)(HEIGHT / perp_wall_dist);
	*draw_start = -(*line_height) / 2 + HEIGHT / 2;
	*draw_end = (*line_height) / 2 + HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	if (*draw_end >= HEIGHT)
		*draw_end = HEIGHT - 1;
}

mlx_image_t	*select_texture(t_scene *scene, t_dda_data *dda, t_wall_data *wall_data)
{
	mlx_image_t	*tex_img;

	if (dda->side == 0)
	{
		if(scene->map[dda->map_y][dda->map_x] ==  'D')
			tex_img = scene->door_img;
		else if (wall_data->ray_dir_x > 0)
			tex_img = scene->img_east;
		else
			tex_img = scene->img_west;
	}
	else
	{
		if(scene->map[dda->map_y][dda->map_x] ==  'D')
			tex_img = scene->door_img;
		else if (wall_data->ray_dir_y > 0)
			tex_img = scene->img_south;
		else
			tex_img = scene->img_north;
	}
	return (tex_img);
}

void	calculate_texture_x(t_player *player, double ray_dir_x, 
							double ray_dir_y, t_texture_data *tex_data)
{
	double	wall_x;

	if (tex_data->side == 0)
		wall_x = player->pos_y + tex_data->perp_wall_dist * ray_dir_y;
	else
		wall_x = player->pos_x + tex_data->perp_wall_dist * ray_dir_x;
	wall_x -= floor(wall_x);
	tex_data->tex_x = (int)(wall_x * (double)tex_data->tex_width);
	if (tex_data->tex_x < 0)
		tex_data->tex_x = 0;
	if (tex_data->tex_x >= tex_data->tex_width)
		tex_data->tex_x = tex_data->tex_width - 1;
	if ((tex_data->side == 0 && ray_dir_x > 0) 
		|| (tex_data->side == 1 && ray_dir_y < 0))
		tex_data->tex_x = tex_data->tex_width - tex_data->tex_x - 1;
}

void	draw_textured_wall_column(mlx_image_t *img, mlx_image_t *tex_img, 
									int x, t_texture_data *tex_data)
{
	int		tex_y;
	int		pixel_index;
	uint8_t	*pixel;
	double	step;
	double	tex_pos;

	step = (double)tex_data->tex_height / tex_data->line_height;
	tex_pos = (tex_data->draw_start - HEIGHT / 2 
			+ tex_data->line_height / 2) * step;
	while (tex_data->draw_start < tex_data->draw_end)
	{
		tex_y = (int)tex_pos; 
		tex_pos += step;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex_data->tex_height)
			tex_y = tex_data->tex_height - 1;
		pixel_index = (tex_y * tex_data->tex_width + tex_data->tex_x) * 4;
		if (pixel_index >= 0 && pixel_index 
			< (tex_data->tex_width * tex_data->tex_height * 4))
		{
			pixel = &tex_img->pixels[pixel_index];
			mlx_put_pixel(img, x, tex_data->draw_start, 
				(pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | 0xFF);
		}
		tex_data->draw_start++;
	}
}

void	draw_textured_wall(mlx_image_t *img, mlx_image_t *tex_img, 
							int x, t_wall_data *wall_data)
{
	t_texture_data	tex_data;

	tex_data.tex_width = tex_img->width;
	tex_data.tex_height = tex_img->height;
	tex_data.side = wall_data->side;
	tex_data.perp_wall_dist = wall_data->perp_wall_dist;
	tex_data.draw_start = wall_data->draw_start;
	tex_data.draw_end = wall_data->draw_end;
	tex_data.line_height = wall_data->line_height;
	calculate_texture_x(wall_data->player, wall_data->ray_dir_x,
		wall_data->ray_dir_y, &tex_data);
	draw_textured_wall_column(img, tex_img, x, &tex_data);
}

void	draw_single_wall_column(mlx_image_t *img, t_scene *scene,
								t_player *player, int x)
{
	t_dda_data	dda;
	int			draw_start;
	int			draw_end;
	int			line_height;
	mlx_image_t	*tex_img;
	t_wall_data	wall_data;

	calculate_ray_direction(x, player, &wall_data);
	calculate_step_and_side_dist(player, &wall_data, &dda);
	perform_dda(scene, &dda);
	calculate_wall_distance(player, &wall_data, &dda);
	calculate_draw_bounds(dda.perp_wall_dist, &draw_start, 
		&draw_end, &line_height);
	tex_img = select_texture(scene, &dda, &wall_data);
	wall_data.player = player;
	wall_data.side = dda.side;
	wall_data.perp_wall_dist = dda.perp_wall_dist;
	wall_data.draw_start = draw_start;
	wall_data.draw_end = draw_end;
	wall_data.line_height = line_height;
	draw_textured_wall(img, tex_img, x, &wall_data);
}
// Constants
#define BASE_GUN_X 250
#define BASE_GUN_Y 420

// Running animation
#define RUN_FREQ     0.25f   // frequency of bobbing when running
#define RUN_AMP_X    5       // sway left-right
#define RUN_AMP_Y    10       // up-down bounce

// Idle breathing animation
#define IDLE_FREQ    0.1f   // slower breathing
#define IDLE_AMP_Y   2       // subtle up-down motion

void	draw_walls(mlx_image_t *img, t_scene *scene, t_player *player)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		draw_single_wall_column(img, scene, player, x);
		x++;
	}
}

#include <math.h>

void draw_gun(t_game_data *game_data, bool is_moving)
{
    static int frame_counter = 0;
    float bob_phase;
    int offset_x = BASE_GUN_X;
    int offset_y = BASE_GUN_Y;

    if (is_moving)
    {
        // Running motion: faster & bouncy
        bob_phase = frame_counter * RUN_FREQ;
        offset_x += (int)(sinf(bob_phase) * RUN_AMP_X);                    // Side-to-side
        offset_y += (int)(fabsf(sinf(bob_phase)) * RUN_AMP_Y);            // Bounce up/down
    }
    else
    {
        // Idle breathing: slow up-down only
        bob_phase = frame_counter * IDLE_FREQ;
        offset_y += (int)(sinf(bob_phase) * IDLE_AMP_Y);                  // Subtle breathing
    }

    // Delete previous gun image if it exists
    if (game_data->scene->gun_image)
    {
        mlx_delete_image(game_data->mlx, game_data->scene->gun_image);
        game_data->scene->gun_image = NULL;
    }

    // Create new gun image
    game_data->scene->gun_image = mlx_texture_to_image(
        game_data->mlx, game_data->scene->gun_texture);

    // Draw to screen
    mlx_image_to_window(game_data->mlx, game_data->scene->gun_image, offset_x, offset_y);

    // Advance frame counter
    frame_counter++;
}



void	game_loop(void *param)
{
	t_game_data	*data;

	data = (t_game_data *) param;
	handle_movement_keys(data->mlx, data->player, data->scene->map);
	draw_floor_and_ceiling(data);
	draw_walls(data->img, data->scene, data->player);
	interact_with_door(data->scene, data->player, data->mlx);
	if (handle_movement_keys(data->mlx, data->player, data->scene->map))
	{
		draw_gun(data, true);
	}
	else
		draw_gun(data, false);

}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game_data	*data;

	data = (t_game_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
}

int	render(t_player *player, t_scene *scene, mlx_t *mlx)
{
	static t_game_data	game_data;
	mlx_image_t			*img;

	if (!mlx)
		return (ft_putstr_fd("MLX not initialized\n", 2), EXIT_FAILURE);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		return (ft_putstr_fd("Error: Failed to create image\n", 2),
			EXIT_FAILURE);
	game_data.mlx = mlx;
	game_data.img = img;
	game_data.scene = scene;
	game_data.player = player;
	draw_floor_and_ceiling(&game_data);
	draw_walls(game_data.img, scene, player);
	if (mlx_image_to_window(game_data.mlx, game_data.img, 0, 0) < 0)
	{
		ft_putstr_fd("Error: Failed to display image\n", 2);
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(mlx, game_loop, &game_data);
	mlx_key_hook(mlx, key_hook, &game_data);
	mlx_loop(mlx);
	return (EXIT_SUCCESS);
}
