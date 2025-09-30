/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movments_utils_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:17:11 by mboutahi          #+#    #+#             */
/*   Updated: 2025/09/30 20:17:50 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#include "../../include/rendering_bonus.h"

void	move_player_forward(t_player *player, char **map)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + player->dir_x * MOVE_SPEED;
	new_y = player->pos_y + player->dir_y * MOVE_SPEED;
	if (can_move_to(map, new_x, player->pos_y))
		player->pos_x = new_x;
	if (can_move_to(map, player->pos_x, new_y))
		player->pos_y = new_y;
}

void	move_player_backward(t_player *player, char **map)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x - player->dir_x * MOVE_SPEED;
	new_y = player->pos_y - player->dir_y * MOVE_SPEED;
	if (can_move_to(map, new_x, player->pos_y))
		player->pos_x = new_x;
	if (can_move_to(map, player->pos_x, new_y))
		player->pos_y = new_y;
}

void	move_player_left(t_player *player, char **map)
{
	double	new_x;
	double	new_y;

	new_y = player->pos_y - player->plane_y * MOVE_SPEED;
	new_x = player->pos_x - player->plane_x * MOVE_SPEED;
	if (can_move_to(map, new_x, player->pos_y))
		player->pos_x = new_x;
	if (can_move_to(map, player->pos_x, new_y))
		player->pos_y = new_y;
}

void	move_player_right(t_player *player, char **map)
{
	double	new_x;
	double	new_y;

	new_y = player->pos_y + player->plane_y * MOVE_SPEED;
	new_x = player->pos_x + player->plane_x * MOVE_SPEED;
	if (can_move_to(map, new_x, player->pos_y))
		player->pos_x = new_x;
	if (can_move_to(map, player->pos_x, new_y))
		player->pos_y = new_y;
}
