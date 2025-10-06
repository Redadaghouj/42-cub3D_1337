/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:30:33 by mboutahi          #+#    #+#             */
/*   Updated: 2025/10/06 10:43:20 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	center_wall(double perp_wall_dist, int *draw_start,
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

mlx_image_t	*select_texture(t_scene *scene, t_dda_data *dda,
		t_wall_data *wall_data)
{
	mlx_image_t	*tex_img;

	if (dda->side == 0)
	{
		if (scene->map[dda->map_y][dda->map_x] == 'D')
			tex_img = scene->door_img;
		else if (wall_data->ray_dir_x > 0)
			tex_img = scene->img_east;
		else
			tex_img = scene->img_west;
	}
	else
	{
		if (scene->map[dda->map_y][dda->map_x] == 'D')
			tex_img = scene->door_img;
		else if (wall_data->ray_dir_y > 0)
			tex_img = scene->img_south;
		else
			tex_img = scene->img_north;
	}
	return (tex_img);
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
