/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:04:11 by redadgh           #+#    #+#             */
/*   Updated: 2025/09/28 20:33:54 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

bool load_textures(t_scene *scene)
{
	int	i;

	scene->tex_north = mlx_load_png(ft_strdup("assets/textures/wall_1.png"));
	scene->tex_south = mlx_load_png(ft_strdup("assets/textures/wall_1.png"));
	scene->tex_west = mlx_load_png(ft_strdup("assets/textures/wall_1.png"));
	scene->tex_east = mlx_load_png(ft_strdup("assets/textures/wall_1.png"));
	scene->door_tex = mlx_load_png(ft_strdup("assets/textures/door.png"));
	scene->hands[0]= mlx_load_png(ft_strdup("assets/textures/hands1.png"));
	scene->hands[1]= mlx_load_png(ft_strdup("assets/textures/hands2.png"));
	scene->hands[2]= mlx_load_png(ft_strdup("assets/textures/hands3.png"));
	scene->hands[3]= mlx_load_png(ft_strdup("assets/textures/hands4.png"));
	scene->hands[4]= mlx_load_png(ft_strdup("assets/textures/hands5.png"));
	// scene->hands[5]= mlx_load_png(ft_strdup("assets/textures/hands_7.png"));
	// scene->hands[6]= mlx_load_png(ft_strdup("assets/textures/hands_8.png"));
	// scene->hands[7]= mlx_load_png(ft_strdup("assets/textures/hands_9.png"));
	// scene->hands[8]= mlx_load_png(ft_strdup("assets/textures/hands_10.png"));
	// scene->hands[9] = mlx_load_png(ft_strdup("assets/textures/hands_11.png"));
	// scene->hands[10] = mlx_load_png(ft_strdup("assets/textures/hands_12.png"));
	// scene->hands[11] = mlx_load_png(ft_strdup("assets/textures/hands_13.png"));
	// scene->hands[12] = mlx_load_png(ft_strdup("assets/textures/hands_14.png"));
	// scene->hands[13] = mlx_load_png(ft_strdup("assets/textures/hands_15.png"));
	// scene->hands[14] = mlx_load_png(ft_strdup("assets/textures/hands_16.png"));
	
	i = -1;
	while (++i < 5 && scene->hands[i])
		;
	if (!scene->tex_north || !scene->tex_south
		|| !scene->tex_west || !scene->tex_east || !scene->door_tex || i < 5)
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
