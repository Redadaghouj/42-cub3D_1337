/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_and_animation_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:32:01 by mboutahi          #+#    #+#             */
/*   Updated: 2025/10/05 13:01:36 by mboutahi         ###   ########.fr       */
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
	int	size;

	size = ((y = (int)player->pos_y - 6), map_size(scene->map));
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
	if ((dx < 1.5 || dy < 1.5)
		&& mlx_is_key_down(mlx, MLX_KEY_E)
		&& scene->map[check_y_open][check_x_open] == 'D')
		scene->map[check_y_open][check_x_open] = 'O';
	close_doors(scene, player);
}

void	draw_gun(t_game_data *game_data, bool is_moving)
{
	static int	frame_counter;
	static int	last_hand_index;
	int			hand_speed;

	hand_speed = HAND_SPEED;
	if (is_moving)
		hand_speed = HAND_SPEED / 2;
	if (last_hand_index % hand_speed == 0)
	{
		if (game_data->scene->last_hands)
		{
			mlx_delete_image(game_data->mlx, game_data->scene->last_hands);
			game_data->scene->last_hands = NULL;
		}
		game_data->scene->last_hands = mlx_texture_to_image(game_data->mlx,
				game_data->scene->hands[frame_counter]);
		mlx_image_to_window(game_data->mlx, game_data->scene->last_hands, 0, 0);
		frame_counter = (frame_counter + 1) % 16;
	}
	last_hand_index++;
}

 void	mouse_move_handler(double x, double y, void *param)
 {
	t_game_data *game;
	double center;

	game = (t_game_data *)param;
	(void)y;
	center = x - WIDTH/2.0;
	if (center < -1.0)
	{
		rotate_player(game->player, -ROT_SPEED * 3);
	}
	else if (center > 1.0)
		rotate_player(game->player, ROT_SPEED * 3);
	mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
}

