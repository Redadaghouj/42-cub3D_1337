/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:16:35 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/24 04:05:21 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	print_ids(t_scene scene)
{
	printf("NO = %s\n", scene.texture.north);
	printf("SO = %s\n", scene.texture.south);
	printf("WE = %s\n", scene.texture.west);
	printf("EA = %s\n", scene.texture.east);
	printf("F = %d,%d,%d\n", scene.floor.r, scene.floor.g, scene.floor.b);
	printf("C = %d,%d,%d\n", scene.ceiling.r, scene.ceiling.g, scene.ceiling.b);
}

bool	check_extension(char *map_path)
{
	char	*ext;
	int		idx;

	ext = ".cub";
	idx = ft_strlen(map_path) - 4;
	if (ft_strcmp(map_path + idx, ext) != 0)
		return (false);
	return (true);
}

int	init_scene(t_scene *scene)
{
	scene->texture.north = NULL;
	scene->texture.south = NULL;
	scene->texture.west = NULL;
	scene->texture.east = NULL;
	scene->floor.is_set = 0;
	scene->ceiling.is_set = 0;
	return (TOTAL_IDS);
}

bool	validate_map(char *map_path, t_scene *scene)
{
	int		fd;
	int		total_ids;

	total_ids = init_scene(scene);
	if (!open_file(map_path, &fd))
		return (exit_with_error(ERR_SCENE_PATH));
	if (!check_extension(map_path))
		return (exit_with_error(ERR_BAD_EXTENSION));
	if (!check_and_fill_ids(fd, scene, &total_ids))
		return (exit_with_error(ERR_INVALID_ID));
	print_ids(*scene);
	free_scene(scene);
	return (true);
}
