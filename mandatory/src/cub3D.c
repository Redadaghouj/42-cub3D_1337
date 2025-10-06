/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:04:11 by redadgh           #+#    #+#             */
/*   Updated: 2025/10/06 12:41:29 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

bool	load_textures(t_scene *scene)
{
	scene->tex_north = mlx_load_png(scene->texture.north);
	scene->tex_south = mlx_load_png(scene->texture.south);
	scene->tex_west = mlx_load_png(scene->texture.west);
	scene->tex_east = mlx_load_png(scene->texture.east);
	if (!scene->tex_north || !scene->tex_south 
		|| !scene->tex_west || !scene->tex_east)
		return (false);
	return (true);
}

void	create_images(mlx_t *mlx, t_scene *scene)
{
	scene->img_north = mlx_texture_to_image(mlx, scene->tex_north);
	scene->img_south = mlx_texture_to_image(mlx, scene->tex_south);
	scene->img_west = mlx_texture_to_image(mlx, scene->tex_west);
	scene->img_east = mlx_texture_to_image(mlx, scene->tex_east);
	if (scene->tex_east)
		mlx_delete_texture(scene->tex_east);
	if (scene->tex_west)
		mlx_delete_texture(scene->tex_west);
	if (scene->tex_north)
		mlx_delete_texture(scene->tex_north);
	if (scene->tex_south)
		mlx_delete_texture(scene->tex_south);
}

int	main(int argc, char *argv[])
{
	t_scene		scene;
	t_player	player;
	t_mlxVar	mlx_v;

	if (argc != 2)
		return (exit_with_error(ERR_USAGE));
	else if (!validate_scene(argv[1], &scene, &player))
	{
		return (free_scene(&scene), EXIT_FAILURE);
	}
	mlx_v.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!mlx_v.mlx)
	{
		ft_putstr_fd("Error\nFailed to initialize MLX\n", 2);
		return (free_scene(&scene), EXIT_FAILURE);
	}
	if (!load_textures(&scene))
		return (free_textures(&scene), free_scene(&scene),
			ft_putstr_fd("Error\nFailed to load some textures\n", 2),
			EXIT_FAILURE);
	create_images(mlx_v.mlx, &scene);
	render(&player, &scene, mlx_v.mlx);
	mlx_terminate(mlx_v.mlx);
	free_scene(&scene);
	return (EXIT_SUCCESS);
}
