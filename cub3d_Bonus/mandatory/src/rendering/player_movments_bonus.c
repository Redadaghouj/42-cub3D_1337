/* ************************************************************************** */
/*                                                                            */
/*   Player movement system with collision detection                         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

bool	can_move_to(char **map, double new_x, double new_y)
{
	int		map_x;
	int		map_y;
	double	buffer;

	map_y = (int)new_y;
	map_x = (int)new_x;
	if (map_y < 0 || map_x < 0 || !map[map_y])
		return false;
	if ((size_t)map_x >= ft_strlen(map[map_y]))
		return false;
	if (map[map_y][map_x] == '1')
		return false;
	buffer = COLLISION_BUFFER;
	int corners[4][2] = {
		{(int)(new_x - buffer), (int)(new_y - buffer)},
		{(int)(new_x + buffer), (int)(new_y - buffer)},
		{(int)(new_x - buffer), (int)(new_y + buffer)},
		{(int)(new_x + buffer), (int)(new_y + buffer)}
	};
	for (int i = 0; i < 4; i++)
	{
		int cx = corners[i][0];
		int cy = corners[i][1];
		if (cy < 0 || cx < 0 || !map[cy])
			return false;
		if ((size_t)cx >= ft_strlen(map[cy]))
			return false;
		if (map[cy][cx] == '1')
			return false;
	}
	return (true);
}

void move_player_forward(t_player *player, char **map)
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

void move_player_backward(t_player *player, char **map)
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

void move_player_left(t_player *player, char **map)
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

void move_player_right(t_player *player, char **map)
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

void rotate_player_left(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(-ROT_SPEED) - player->dir_y * sin(-ROT_SPEED);
	player->dir_y = old_dir_x * sin(-ROT_SPEED) + player->dir_y * cos(-ROT_SPEED);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(-ROT_SPEED) - player->plane_y * sin(-ROT_SPEED);
	player->plane_y = old_plane_x * sin(-ROT_SPEED) + player->plane_y * cos(-ROT_SPEED);
}

void rotate_player_right(t_player *player)
{
	double	old_dir_x;
	double	old_plane_x; 

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(ROT_SPEED) - player->dir_y * sin(ROT_SPEED);
	player->dir_y = old_dir_x * sin(ROT_SPEED) + player->dir_y * cos(ROT_SPEED);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(ROT_SPEED) - player->plane_y * sin(ROT_SPEED);
	player->plane_y = old_plane_x * sin(ROT_SPEED) + player->plane_y * cos(ROT_SPEED);

}

int	handle_movement_keys(mlx_t *mlx, t_player *player, char **map)
{
	int i = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		move_player_forward(player, map);
		i = 1;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		move_player_backward(player, map);
		i = 1;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_player_left(player, map);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_player_right(player, map);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		rotate_player_left(player);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		rotate_player_right(player);
		return (i);
}
