/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 20:35:22 by redadgh           #+#    #+#             */
/*   Updated: 2025/10/05 17:32:14 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	draw_tile(t_game_data *game_data, t_minimap_data minimap, int color)
{
	int	i;
	int	j;
	int	y;
	int	x;

	i = 0;
	y = minimap.screen_y;
	x = minimap.screen_x;
	while (i < BLOCK_SIZE)
	{
		j = 0;
		while (j < BLOCK_SIZE)
		{
			mlx_put_pixel(game_data->img,
				MINIMAP_START + (x * BLOCK_SIZE) + j,
				MINIMAP_START + (y * BLOCK_SIZE) + i, color);
			j++;
		}
		i++;
	}
}

void	minimap_skip(t_minimap_data *minimap)
{
	minimap->map_y++;
	minimap->screen_y++;
}

void	minimap_row(t_game_data *game, t_minimap_data *minimap)
{
	char	tile;
	char	**map;

	map = game->scene->map;
	minimap->screen_x = 0;
	minimap->map_x = minimap->start_x;
	while (minimap->map_x <= minimap->end_x)
	{
		if (map[minimap->map_y]
			&& minimap->map_x >= 0
			&& minimap->map_x < (int)ft_strlen(map[minimap->map_y]))
		{
			tile = map[minimap->map_y][minimap->map_x];
			if (tile == '1')
				draw_tile(game, *minimap, MINIMAP_WALL_COLOR);
			else if (tile == 'D')
				draw_tile(game, *minimap, MINIMAP_DOOR_COLOR);
		}
		minimap->map_x++;
		minimap->screen_x++;
	}
	minimap->map_y++;
	minimap->screen_y++;
}

void	init_minimap_data(t_game_data *game_data, t_minimap_data *minimap_data)
{
	int	player_y;
	int	player_x;

	player_y = (int)game_data->player->pos_y;
	player_x = (int)game_data->player->pos_x;
	minimap_data->start_y = player_y - MINIMAP_RADIUS;
	minimap_data->end_y = player_y + MINIMAP_RADIUS;
	minimap_data->start_x = player_x - MINIMAP_RADIUS;
	minimap_data->end_x = player_x + MINIMAP_RADIUS;
	minimap_data->map_height = 0;
	while (game_data->scene->map[minimap_data->map_height])
		minimap_data->map_height++;
	minimap_data->screen_y = 0;
	minimap_data->map_y = minimap_data->start_y;
}
