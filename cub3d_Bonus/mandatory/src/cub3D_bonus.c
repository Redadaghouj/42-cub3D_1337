/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:04:11 by redadgh           #+#    #+#             */
/*   Updated: 2025/09/25 16:01:31 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

bool load_textures(t_scene *scene)
{
	scene->tex_north = mlx_load_png(ft_strdup("assets/textures/wall_1.png"));
	scene->tex_south = mlx_load_png(ft_strdup("assets/textures/wall_1.png"));
	scene->tex_west = mlx_load_png(ft_strdup("assets/textures/wall_1.png"));
	scene->tex_east = mlx_load_png(ft_strdup("assets/textures/wall_1.png"));
	scene->door_tex = mlx_load_png(ft_strdup("assets/textures/door.png"));

	if (!scene->tex_north || !scene->tex_south || !scene->tex_west || !scene->tex_east)
		return false;
	return true;
}

void create_images(mlx_t *mlx, t_scene *scene)
{
	scene->img_north = mlx_texture_to_image(mlx, scene->tex_north);
	scene->img_south = mlx_texture_to_image(mlx, scene->tex_south);
	scene->img_west = mlx_texture_to_image(mlx, scene->tex_west);
	scene->img_east = mlx_texture_to_image(mlx, scene->tex_east);
	scene->door_img =  mlx_texture_to_image(mlx, scene->door_tex);

}

int main(int argc, char *argv[])
{
	t_scene		scene;
	t_player	player;
	t_mlxVar	mlx_v;
	
	if (argc != 2)
		return (exit_with_error(ERR_USAGE));
	else if (!validate_scene(argv[1], &scene, &player))
	{
		free_scene(&scene);
		return (EXIT_FAILURE);
	}
	mlx_v.mlx = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	if (!mlx_v.mlx)
	{
		ft_putstr_fd("Failed to initialize MLX\n", 2);
		free_scene(&scene);
		return (EXIT_FAILURE);
	}
	if (!load_textures(&scene))
		ft_putstr_fd("Warning: Failed to load some textures, using fallbacks\n", 2);
	create_images(mlx_v.mlx, &scene);
	render(&player, &scene, mlx_v.mlx);
	mlx_terminate(mlx_v.mlx);
	free_scene(&scene);
	return (EXIT_SUCCESS);
}
