/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_and_animation_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:32:01 by mboutahi          #+#    #+#             */
/*   Updated: 2025/10/02 22:07:47 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	map_size(char **map)
{
	int	i;
	
	i = 0;
	
	while (map[i] != NULL)
	{
		i++;
	}
	return (i);
}
void	close_doors(t_scene *scene, t_player *player)
{
	int	y;
	int	x;
	int	dx;
	int	dy;
	int size;
	
	size = map_size(scene->map);
	y = (int)player->pos_y - 6;
	while (++y <= (int)player->pos_y + 6)
	{
		if (y < 0 || y >= size)
			continue ;
		x = (int)player->pos_x - 6;
		while (++x <= (int)player->pos_x + 6)
		{
			if (x < 0 || x >= (int)ft_strlen(scene->map[y]))
				continue ;
			if (scene->map[y][x] == 'O')
			{
				dx = abs(x - (int)player->pos_x);
				dy = abs(y - (int)player->pos_y);
				if (dx > 1 || dy > 1)
					scene->map[y][x] = 'D';
			}
		}
	}
}

void	interact_with_door(t_scene *scene, t_player *player, mlx_t *mlx)
{
	int		check_x_open;
	int		check_y_open;
	double	dx;
	double	dy;

	check_y_open = (int)(player->pos_y + player->dir_y);
	check_x_open = (int)(player->pos_x + player->dir_x);
	if (check_x_open < 0 || check_y_open < 0 || !scene->map[check_y_open]
		|| check_x_open >= (int)ft_strlen(scene->map[check_y_open]))
		return ;
	dx = player->pos_x - (check_x_open + 0.5);
	dy = player->pos_y - (check_y_open + 0.5);
	if (sqrt(dx * dx + dy * dy) < 1.5
		&& mlx_is_key_down(mlx, MLX_KEY_E)
		&& scene->map[check_y_open][check_x_open] == 'D')
		scene->map[check_y_open][check_x_open] = 'O';
	close_doors(scene, player);
}

void	draw_gun(t_game_data *game_data, bool is_moving)
{
	static int	frame_counter = 0;
	int			offset_x;
	int			offset_y;	

	offset_x = BASE_GUN_X;
	offset_y = BASE_GUN_Y;
	if (is_moving)
	{
		offset_x += (int)(sinf(frame_counter * RUN_FREQ) * RUN_AMP_X);
		offset_y += (int)(fabsf(sinf(frame_counter * RUN_FREQ)) * RUN_AMP_Y);
	}
	else
		offset_y += (int)(sinf(frame_counter * IDLE_FREQ) * IDLE_AMP_Y);
	if (game_data->scene->gun_image)
	{
		mlx_delete_image(game_data->mlx, game_data->scene->gun_image);
		game_data->scene->gun_image = NULL;
	}
	game_data->scene->gun_image = mlx_texture_to_image(
			game_data->mlx, game_data->scene->gun_texture);
	mlx_image_to_window(game_data->mlx, game_data->scene->gun_image,
		offset_x, offset_y);
	frame_counter++;
}
