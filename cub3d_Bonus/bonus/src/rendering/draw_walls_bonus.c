/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:31:40 by mboutahi          #+#    #+#             */
/*   Updated: 2025/09/30 20:31:55 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#include "../../include/rendering_bonus.h"

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
	if ((tex_data->side == 0 && ray_dir_x < 0) 
		|| (tex_data->side == 1 && ray_dir_y > 0))
		tex_data->tex_x = tex_data->tex_width - tex_data->tex_x - 1;
}

void	draw_textured_wall_column(mlx_image_t *img, mlx_image_t *tex_img, 
									int x, t_texture_data *tex_data)
{
	int		p;
	uint8_t	*pixel;
	double	step;
	double	tex_pos;

	step = (double)tex_data->tex_height / tex_data->line_height;
	tex_pos = (tex_data->draw_start - HEIGHT / 2 
			+ tex_data->line_height / 2) * step;
	while (tex_data->draw_start < tex_data->draw_end)
	{
		if (tex_pos < 0)
			tex_pos = 0;
		if (tex_pos >= tex_data->tex_height)
			tex_pos = tex_data->tex_height - 1;
		p = ((int)tex_pos * tex_data->tex_width + tex_data->tex_x) * 4;
		if (p >= 0 && p 
			< (tex_data->tex_width * tex_data->tex_height * 4))
		{
			pixel = &tex_img->pixels[p];
			mlx_put_pixel(img, x, tex_data->draw_start, 
				(pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | 0xFF);
		}
		tex_data->draw_start++;
		tex_pos += step;
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
	t_wall_data	wall_data;

	calculate_ray_direction(x, player, &wall_data);
	calculate_step_and_side_dist(player, &wall_data, &dda);
	perform_dda(scene, &dda);
	calculate_wall_distance(player, &wall_data, &dda);
	calculate_draw_bounds(dda.perp_wall_dist, &draw_start, 
		&draw_end, &line_height);
	wall_data.player = player;
	wall_data.side = dda.side;
	wall_data.perp_wall_dist = dda.perp_wall_dist;
	wall_data.draw_start = draw_start;
	wall_data.draw_end = draw_end;
	wall_data.line_height = line_height;
	draw_textured_wall(img, select_texture(scene, &dda, &wall_data),
		x, &wall_data);
}

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
