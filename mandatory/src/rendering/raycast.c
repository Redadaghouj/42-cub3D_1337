/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:16:09 by mboutahi          #+#    #+#             */
/*   Updated: 2025/10/06 11:17:41 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	calculate_ray_direction(double x, t_player *player, 
								t_wall_data *wall_data)
{
	double	scale_x;

	scale_x = 2 * x / (double)WIDTH - 1;
	wall_data->ray_dir_x = player->dir_x + player->plane_x * scale_x;
	wall_data->ray_dir_y = player->dir_y + player->plane_y * scale_x;
	if (wall_data->ray_dir_x == 0.0)
		wall_data->ray_dir_x = 1e-30;
	if (wall_data->ray_dir_y == 0.0)
		wall_data->ray_dir_y = 1e-30;
}

void	calculate_step_and_ray_mov(t_player *player, t_wall_data *wall_data, 
									t_dda_data *dda)
{
	dda->map_x = (int)player->pos_x;
	dda->map_y = (int)player->pos_y;
	dda->ray_unit_x = fabs(1 / wall_data->ray_dir_x);
	dda->ray_unit_y = fabs(1 / wall_data->ray_dir_y);
	if (wall_data->ray_dir_x < 0)
		dda->step_x = (dda->ray_mov_x = (player->pos_x - dda->map_x)
				* dda->ray_unit_x, -1);
	else
	{
		dda->step_x = 1;
		dda->ray_mov_x = (dda->map_x + 1.0 - player->pos_x)
			* dda->ray_unit_x;
	}
	if (wall_data->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->ray_mov_y = (player->pos_y - dda->map_y) * dda->ray_unit_y;
	}
	else
	{
		dda->step_y = 1;
		dda->ray_mov_y = (dda->map_y + 1.0 - player->pos_y) 
			* dda->ray_unit_y;
	}
}

void	perform_dda(t_scene *scene, t_dda_data *dda)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (dda->ray_mov_x < dda->ray_mov_y)
		{
			dda->ray_mov_x += dda->ray_unit_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->ray_mov_y += dda->ray_unit_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (dda->map_x < 0 || dda->map_y < 0 || scene->map[dda->map_y] == NULL)
			hit = 1;
		else if (dda->map_x >= (int)ft_strlen(scene->map[dda->map_y]))
			hit = 1;
		else if (scene->map[dda->map_y][dda->map_x] == '1'
			|| scene->map[dda->map_y][dda->map_x] == 'D')
			hit = 1;
	}
}

void	calculate_wall_distance(t_player *player, t_wall_data *wall_data,
								t_dda_data *dda)
{
	if (dda->side == 0)
		dda->ray_wall_dist = (dda->map_x - player->pos_x 
				+ (1 - dda->step_x) / 2) / wall_data->ray_dir_x;
	else
		dda->ray_wall_dist = (dda->map_y - player->pos_y 
				+ (1 - dda->step_y) / 2) / wall_data->ray_dir_y;
}

void	free_textures(t_scene *scene)
{
	if (scene->tex_east)
		mlx_delete_texture(scene->tex_east);
	if (scene->tex_west)
		mlx_delete_texture(scene->tex_west);
	if (scene->tex_north)
		mlx_delete_texture(scene->tex_north);
	if (scene->tex_south)
		mlx_delete_texture(scene->tex_south);
}
