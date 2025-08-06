/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 04:19:39 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/27 17:00:11 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

unsigned int color_to_int(t_color c)
{
	return (c.r << 24) | (c.g << 16) | (c.b << 8) | 0xFF;
}

// #include <stdlib.h>
// #include <string.h>

// // Debug function to check if textures are properly loaded
// void debug_textures(t_scene *scene)
// {
// 	printf("=== TEXTURE DEBUG INFO ===\n");
// 	printf("North texture: %p", (void*)scene->img_north);
// 	if (scene->img_north)
// 		printf(" (size: %dx%d, pixels: %p)\n", scene->img_north->width, scene->img_north->height, (void*)scene->img_north->pixels);
// 	else
// 		printf(" (NULL)\n");
		
// 	printf("South texture: %p", (void*)scene->img_south);
// 	if (scene->img_south)
// 		printf(" (size: %dx%d, pixels: %p)\n", scene->img_south->width, scene->img_south->height, (void*)scene->img_south->pixels);
// 	else
// 		printf(" (NULL)\n");
		
// 	printf("East texture: %p", (void*)scene->img_east);
// 	if (scene->img_east)
// 		printf(" (size: %dx%d, pixels: %p)\n", scene->img_east->width, scene->img_east->height, (void*)scene->img_east->pixels);
// 	else
// 		printf(" (NULL)\n");
		
// 	printf("West texture: %p", (void*)scene->img_west);
// 	if (scene->img_west)
// 		printf(" (size: %dx%d, pixels: %p)\n", scene->img_west->width, scene->img_west->height, (void*)scene->img_west->pixels);
// 	else
// 		printf(" (NULL)\n");
// 	printf("==========================\n");
// }

void draw_floor_and_ceiling(mlx_image_t *img, t_scene *scene)
{
	int y;
	int x;
	unsigned int ceil_color;
	unsigned int floor_color;

	ceil_color = color_to_int(scene->ceiling);
	floor_color = color_to_int(scene->floor);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(img, x, y, ceil_color);
			else
				mlx_put_pixel(img, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void draw_walls(mlx_image_t *img, t_scene *scene, t_player *player)
{
	int x = 0;

	// if (player->dir_x == 0.0 && player->dir_y == 0.0)
	// {
	// 	printf("ERROR: Player direction is zero! Setting default direction.\n");
	// 	player->dir_x = -1.0;
	// 	player->dir_y = 0.0;
	// 	player->plane_x = 0.0;
	// 	player->plane_y = 0.66;
	// }
	while (x < WIDTH)
	{
		double camera_x = 2 * x / (double)WIDTH - 1;
		double ray_dir_x = player->dir_x + player->plane_x * camera_x;
		double ray_dir_y = player->dir_y + player->plane_y * camera_x;

		if (ray_dir_x == 0.0) ray_dir_x = 1e-30;
		if (ray_dir_y == 0.0) ray_dir_y = 1e-30;

		int map_x = (int)player->pos_x;
		int map_y = (int)player->pos_y;
		double side_dist_x;
		double side_dist_y;
		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);
		double perp_wall_dist;
		int step_x;
		int step_y;
		int hit = 0;
		int side;
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (player->pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - player->pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (player->pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - player->pos_y) * delta_dist_y;
		}
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (map_x < 0 || map_y < 0 || scene->map[map_y] == NULL || map_x >= (int)ft_strlen(scene->map[map_y]))
				hit = 1;
			else if (scene->map[map_y][map_x] == '1')
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (map_x - player->pos_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - player->pos_y + (1 - step_y) / 2) / ray_dir_y;
		int line_height = (int)(HEIGHT / perp_wall_dist);
		int draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;
		mlx_image_t *tex_img;
		if (side == 0)
		{
			if (ray_dir_x > 0)
				tex_img = scene->img_west;
			else
				tex_img = scene->img_east;
		}
		else
		{
			if (ray_dir_y > 0)
				tex_img = scene->img_north;
			else
				tex_img = scene->img_south;
		}
		if (!tex_img || !tex_img->pixels)
		{
			uint32_t wall_color = 0xFF0000FF;
			int y = draw_start;
			while (y < draw_end)
			{
				mlx_put_pixel(img, x, y, wall_color);
				y++;
			}
		}
		else
		{
			int tex_width = tex_img->width;
			int tex_height = tex_img->height;
			double wall_x;
			if (side == 0)
				wall_x = player->pos_y + perp_wall_dist * ray_dir_y;
			else
				wall_x = player->pos_x + perp_wall_dist * ray_dir_x;
			wall_x -= floor(wall_x);
			int tex_x = (int)(wall_x * (double)tex_width);
			if (tex_x < 0) tex_x = 0;
			if (tex_x >= tex_width) tex_x = tex_width - 1;
			if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
				tex_x = tex_width - tex_x - 1;
			int y = draw_start;
			while (y < draw_end)
			{
				int d = y * 256 - HEIGHT * 128 + line_height * 128;
				int tex_y = ((d * tex_height) / line_height) / 256;
				if (tex_y < 0) tex_y = 0;
				if (tex_y >= tex_height) tex_y = tex_height - 1;
				int pixel_index = (tex_y * tex_width + tex_x) * 4;
				if (pixel_index >= 0 && pixel_index < (tex_width * tex_height * 4))
				{
					uint8_t *pixel = &tex_img->pixels[pixel_index];
					uint32_t color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | 0xFF;
					mlx_put_pixel(img, x, y, color);
				}
				else
					mlx_put_pixel(img, x, y, 0xFF00FFFF);
				y++;
			}
		}
		x++;
	}
}
void game_loop(void* param)
{
	t_game_data *data = (t_game_data*)param;
	draw_floor_and_ceiling(data->img, data->scene);
	draw_walls(data->img, data->scene, data->player);
}
void key_hook(mlx_key_data_t keydata, void* param)
{
	t_game_data *data = (t_game_data*)param;
	
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
}

int render(t_player *player, t_scene *scene, mlx_t *mlx)
{
	static t_game_data game_data;
	// debug_textures(scene);
	if (!mlx)
	{
		ft_putstr_fd("MLX not initialized\n", 2);
		return (EXIT_FAILURE);
	}

	mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
	{
		ft_putstr_fd("Error: Failed to create image\n", 2);
		return (EXIT_FAILURE);
	}
	game_data.mlx = mlx;
	game_data.img = img;
	game_data.scene = scene;
	game_data.player = player;
	draw_floor_and_ceiling(img, scene);
	draw_walls(img, scene, player);
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
	{
		ft_putstr_fd("Error: Failed to display image\n", 2);
		return (EXIT_FAILURE);
	}
	mlx_loop_hook(mlx, game_loop, &game_data);
	mlx_key_hook(mlx, key_hook, &game_data);
	mlx_loop(mlx);
	return (EXIT_SUCCESS);
}