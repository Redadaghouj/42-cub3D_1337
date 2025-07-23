/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:16:35 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/23 02:56:43 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

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

bool	open_file(char *file_name, int *fd)
{
	*fd = open(file_name, O_RDONLY);
	if (*fd < 0)
		return (false);
	return (true);
}

bool	check_and_fill_ids(int fd, t_scene *scene, int *total_ids)
{
	return (true);
}

bool	validate_map(char *map_path)
{
	int		fd;
	int		total_ids;
	t_scene	scene;

	total_ids = 6;
	if (!open_file(map_path, &fd))
		return (exit_with_error(ERR_SCENE_PATH));
	if (!check_extension(map_path))
		return (exit_with_error(ERR_BAD_EXTENSION));
	if (!check_and_fill_ids(fd, &scene, &total_ids))
		return (exit_with_error(ERR_INVALID_ID));
	return (true);
}
