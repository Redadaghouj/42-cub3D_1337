/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:18:17 by mboutahi          #+#    #+#             */
/*   Updated: 2025/10/04 13:09:08 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

bool	corner_check(char **map, int corners[4][2])
{
	int	i;
	int	cx;
	int	cy;

	i = 0;
	while (i < 4)
	{
		cx = corners[i][0];
		cy = corners[i][1];
		if (cy < 0 || cx < 0 || !map[cy])
			return (false);
		if ((size_t)cx >= ft_strlen(map[cy]))
			return (false);
		if (map[cy][cx] == '1' || map[cy][cx] == 'D')
			return (false);
		i++;
	}
	return (true);
}

bool	can_move_to(char **map, double new_x, double new_y)
{
	int	corners[4][2];
	int	map_x;
	int	map_y;

	map_y = (int)new_y;
	map_x = (int)new_x;
	if (map_y < 0 || map_x < 0 || !map[map_y])
		return (false);
	if ((size_t)map_x >= ft_strlen(map[map_y]))
		return (false);
	if (map[map_y][map_x] == '1' || map[map_y][map_x] == 'D')
		return (false);
	corners[0][0] = (int)(new_x - COLLISION_BUFFER);
	corners[0][1] = (int)(new_y - COLLISION_BUFFER);
	corners[1][0] = (int)(new_x - COLLISION_BUFFER);
	corners[1][1] = (int)(new_y + COLLISION_BUFFER);
	corners[2][0] = (int)(new_x + COLLISION_BUFFER);
	corners[2][1] = (int)(new_y - COLLISION_BUFFER);
	corners[3][0] = (int)(new_x + COLLISION_BUFFER);
	corners[3][1] = (int)(new_y + COLLISION_BUFFER);
	return (corner_check(map, corners));
}

void	rotate_player_right(t_player *player)
{
	player->angle += ROT_SPEED;
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->plane_x = -sin(player->angle) * 0.66;
	player->plane_y = cos(player->angle) * 0.66;
}

void	rotate_player_left(t_player *player)
{
	player->angle -= ROT_SPEED;
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->plane_x = -sin(player->angle) * 0.66;
	player->plane_y = cos(player->angle) * 0.66;
}

void	handle_movement_keys(mlx_t *mlx, t_player *player, char **map)
{
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move_player_forward(player, map);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		move_player_backward(player, map);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_player_left(player, map);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_player_right(player, map);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		rotate_player_left(player);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		rotate_player_right(player);
}
