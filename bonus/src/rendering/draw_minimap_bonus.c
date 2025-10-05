/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 20:35:22 by redadgh           #+#    #+#             */
/*   Updated: 2025/10/05 17:50:09 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

void	draw_minimap_bg(t_game_data *game_data)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_HEIGHT)
	{
		j = 0;
		while (j < MINIMAP_WIDTH)
		{
			mlx_put_pixel(game_data->img, i + MINIMAP_START,
				j + MINIMAP_START, MINIMAP_BG_COLOR);
			j++;
		}
		i++;
	}
}

void	draw_minimap_view(t_game_data *game, t_minimap_data *minimap)
{
	while (minimap->map_y <= minimap->end_y
		&& minimap->map_y < minimap->map_height)
	{
		if (minimap->map_y < 0 || minimap->map_y >= minimap->map_height)
			minimap_skip(minimap);
		else
			minimap_row(game, minimap);
	}
}

void	draw_minimap_player(t_game_data *game_data)
{
	int	center_x;
	int	center_y;
	int	i;
	int	j;

	center_x = MINIMAP_START + (MINIMAP_RADIUS * BLOCK_SIZE) + (BLOCK_SIZE / 2);
	center_y = MINIMAP_START + (MINIMAP_RADIUS * BLOCK_SIZE) + (BLOCK_SIZE / 2);
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			mlx_put_pixel(game_data->img, center_x + j,
				center_y + i, MINIMAP_PLAYER_COLOR);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game_data *game_data)
{
	t_minimap_data	minimap_data;

	init_minimap_data(game_data, &minimap_data);
	draw_minimap_bg(game_data);
	draw_minimap_view(game_data, &minimap_data);
	draw_minimap_player(game_data);
}
