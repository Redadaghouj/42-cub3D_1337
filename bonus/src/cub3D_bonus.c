/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:04:11 by redadgh           #+#    #+#             */
/*   Updated: 2025/10/06 11:46:30 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D_bonus.h"

bool	check_frames(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		if (!scene->hands[i])
			return (false);
		i++;
	}
	return (true);
}

bool	load_textures(t_scene *scene)
{
	scene->tex_north = mlx_load_png(scene->texture.north);
	scene->tex_south = mlx_load_png(scene->texture.south);
	scene->tex_west = mlx_load_png(scene->texture.west);
	scene->tex_east = mlx_load_png(scene->texture.east);
	scene->door_tex = mlx_load_png(scene->texture.door);
	scene->hands[0] = mlx_load_png("assets/textures/frame_00.png");
	scene->hands[1] = mlx_load_png("assets/textures/frame_01.png");
	scene->hands[2] = mlx_load_png("assets/textures/frame_02.png");
	scene->hands[3] = mlx_load_png("assets/textures/frame_03.png");
	scene->hands[4] = mlx_load_png("assets/textures/frame_04.png");
	scene->hands[5] = mlx_load_png("assets/textures/frame_05.png");
	scene->hands[6] = mlx_load_png("assets/textures/frame_06.png");
	scene->hands[7] = mlx_load_png("assets/textures/frame_07.png");
	scene->hands[8] = mlx_load_png("assets/textures/frame_08.png");
	scene->hands[9] = mlx_load_png("assets/textures/frame_09.png");
	scene->hands[10] = mlx_load_png("assets/textures/frame_10.png");
	scene->hands[11] = mlx_load_png("assets/textures/frame_11.png");
	scene->hands[12] = mlx_load_png("assets/textures/frame_12.png");
	scene->hands[13] = mlx_load_png("assets/textures/frame_13.png");
	scene->hands[14] = mlx_load_png("assets/textures/frame_14.png");
	scene->hands[15] = mlx_load_png("assets/textures/frame_15.png");
	if (!scene->tex_north || !scene->tex_south || !scene->tex_west
		|| !scene->tex_east || !scene->door_tex || !check_frames(scene))
		return (false);
	return (true);
}

void	create_images(mlx_t *mlx, t_scene *scene)
{
	scene->img_north = mlx_texture_to_image(mlx, scene->tex_north);
	scene->img_south = mlx_texture_to_image(mlx, scene->tex_south);
	scene->img_west = mlx_texture_to_image(mlx, scene->tex_west);
	scene->img_east = mlx_texture_to_image(mlx, scene->tex_east);
	scene->door_img = mlx_texture_to_image(mlx, scene->door_tex);
	if (scene->tex_east)
		mlx_delete_texture(scene->tex_east);
	if (scene->tex_west)
		mlx_delete_texture(scene->tex_west);
	if (scene->tex_north)
		mlx_delete_texture(scene->tex_north);
	if (scene->tex_south)
		mlx_delete_texture(scene->tex_south);
	if (scene->door_tex)
		mlx_delete_texture(scene->door_tex);
}

int	main(int argc, char *argv[])
{
	t_scene		scene;
	t_player	player;
	t_mlxVar	mlx_v;

	if (argc != 2)
		return (exit_with_error(ERR_USAGE));
	else if (!validate_scene(argv[1], &scene, &player))
		return (free_scene(&scene), EXIT_FAILURE);
	mlx_v.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!mlx_v.mlx)
	{
		ft_putstr_fd("Error\nFailed to initialize MLX\n", 2);
		return (free_scene(&scene), EXIT_FAILURE);
	}
	if (!load_textures(&scene))
		return (free_tex(&scene), free_textures(&scene),
			ft_putstr_fd("Error\nFailed to load some textures\n", 2),
			free_scene(&scene), EXIT_FAILURE);
	create_images(mlx_v.mlx, &scene);
	render(&player, &scene, mlx_v.mlx);
	mlx_terminate(mlx_v.mlx);
	free_scene(&scene);
	return (EXIT_SUCCESS);
}
