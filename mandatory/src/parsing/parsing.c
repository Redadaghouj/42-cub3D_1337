/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:16:35 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/27 02:31:41 by redadgh          ###   ########.fr       */
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

void	print_map(char **map)
{
	int	i;
	int	j;

	if (!map)
		return ;
	i = 0;
	printf("\n");
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			printf("%c", map[i][j]);
			j++;
		}
		i++;
		printf("\n");
	}
}

bool	check_extension(char *map_path)
{
	char	*ext;
	int		idx;

	ext = ".cub";
	idx = ft_strlen(map_path) - ft_strlen(ext);
	if (ft_strcmp(map_path + idx, ext) != 0)
		return (false);
	return (true);
}

void	init_scene(t_scene *scene)
{
	scene->texture.north = NULL;
	scene->texture.south = NULL;
	scene->texture.west = NULL;
	scene->texture.east = NULL;
	scene->map = NULL;
	scene->floor.is_set = 0;
	scene->ceiling.is_set = 0;
}

bool	validate_scene(char *map_path, t_scene *scene, t_player *player)
{
	int		fd;

	init_scene(scene);
	if (!open_file(map_path, &fd))
		return (exit_with_error(ERR_SCENE_PATH));
	if (!check_extension(map_path))
		return (exit_with_error(ERR_BAD_EXTENSION));
	if (!parse_identifiers(fd, scene))
		return (exit_with_error(ERR_INVALID_ID));
	if (!parse_map(fd, scene, player))
		return (exit_with_error(ERR_INVALID_MAP));
	print_ids(*scene);
	print_map(scene->map);
	return (true);
}
