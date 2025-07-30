/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 04:19:39 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/27 17:00:11 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	draw_floor_and_ceiling(mlx_image_t *img, t_scene *scene)
{
	int			y;
	int			x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				mlx_put_pixel(img, x, y, scene->ceiling);
			else
				mlx_put_pixel(img, x, y, scene->floor);
			x++;
		}
		y++;
	}
}

int	render(void)
{
	t_mlxVar	mlx_v;
	t_scene		scene;

	scene.floor = COLOR_BROWN;
	scene.ceiling = COLOR_BLUE_SKY;
	mlx_v.mlx = mlx_init(WIDTH, HEIGHT, "MLX42 Window", true);
	if (!mlx_v.mlx)
	{
		ft_putstr_fd("Failed to initialize MLX\n", 2);
		return (EXIT_FAILURE);
	}

	mlx_v.img = mlx_new_image(mlx_v.mlx, WIDTH, HEIGHT);
	if (!mlx_v.img)
	{
		ft_putstr_fd("Error: Failed to create image\n", 2);
		mlx_terminate(mlx_v.mlx);
		exit(EXIT_FAILURE);
	}
	draw_floor_and_ceiling(mlx_v.img, &scene);
	mlx_image_to_window(mlx_v.mlx, mlx_v.img, 0, 0);
	mlx_loop(mlx_v.mlx);
	mlx_terminate(mlx_v.mlx);
	return (EXIT_SUCCESS);
}
