/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 04:19:39 by redadgh           #+#    #+#             */
/*   Updated: 2025/10/06 10:46:21 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

unsigned int	color_to_int(t_color c)
{
	return ((c.r << 24) | (c.g << 16) | (c.b << 8) | 0xFF);
}

void	draw_floor_and_ceiling(mlx_image_t *img, t_scene *scene)
{
	int				y;
	int				x;
	unsigned int	ceil_color;
	unsigned int	floor_color;

	ceil_color = color_to_int(scene->ceiling);
	floor_color = color_to_int(scene->floor);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(img, x, y, ceil_color);
			else
				mlx_put_pixel(img, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void	game_loop(void *param)
{
	t_game_data	*data;

	data = (t_game_data *) param;
	handle_movement_keys(data->mlx, data->player, data->scene->map);
	draw_floor_and_ceiling(data->img, data->scene);
	draw_walls(data->img, data->scene, data->player);
	interact_with_door(data->scene, data->player, data->mlx);
	if (handle_movement_keys(data->mlx, data->player, data->scene->map))
	{
		draw_gun(data, true);
	}
	else
		draw_gun(data, false);
	draw_minimap(data);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game_data	*data;
	int			i;

	i = 0;
	data = (t_game_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		while (i < 16)
		{
			if (data->scene->hands[i])
				mlx_delete_texture(data->scene->hands[i]);
			i++;
		}
		mlx_close_window(data->mlx);
	}
}

int	render(t_player *player, t_scene *scene, mlx_t *mlx)
{
	static t_game_data	game_data;
	mlx_image_t			*img;

	if (!mlx)
		return (free_tex(scene), ft_putstr_fd("Error\nMLX not initialized\n", 2),
			EXIT_FAILURE);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		return (free_tex(scene),
			ft_putstr_fd("Error\nFailed to create image\n", 2), EXIT_FAILURE);
	game_data.mlx = mlx;
	game_data.img = img;
	game_data.scene = scene;
	game_data.player = player;
	draw_floor_and_ceiling(img, scene);
	draw_walls(img, scene, player);
	if (mlx_image_to_window(game_data.mlx, game_data.img, 0, 0) < 0)
		return (free_tex(scene),
			ft_putstr_fd("Error\nFailed to display image\n", 2),
			free_tex(scene), EXIT_FAILURE);
	mlx_loop_hook(mlx, game_loop, &game_data);
	mlx_key_hook(mlx, key_hook, &game_data);
	mlx_cursor_hook(mlx, mouse_move_handler, &game_data);
	mlx_loop(mlx);
	return (EXIT_SUCCESS);
}
