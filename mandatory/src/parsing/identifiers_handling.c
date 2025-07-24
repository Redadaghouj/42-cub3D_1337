/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiers_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:28:47 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/24 04:19:20 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

unsigned int	bump_id(unsigned int id_type, int *i, int num)
{
	*i += num;
	return (id_type);
}

unsigned int	is_id(char *line, int *i)
{
	*i = skip_leading_spaces(line);
	if (!ft_strncmp(line + *i, "NO ", 3))
		return (bump_id(ID_NO, i, 3));
	else if (!ft_strncmp(line + *i, "SO ", 3))
		return (bump_id(ID_SO, i, 3));
	else if (!ft_strncmp(line + *i, "WE ", 3))
		return (bump_id(ID_WE, i, 3));
	else if (!ft_strncmp(line + *i, "EA ", 3))
		return (bump_id(ID_EA, i, 3));
	else if (!ft_strncmp(line + *i, "F ", 2))
		return (bump_id(ID_F, i, 2));
	else if (!ft_strncmp(line + *i, "C ", 2))
		return (bump_id(ID_C, i, 2));
	else
		return (ID_INVALID);
}

bool	fill_id(unsigned int id_type, t_scene *scene, char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line);
	if (!trimmed)
		return (false);
	if (id_type == ID_NO && !scene->texture.north)
		scene->texture.north = trimmed;
	else if (id_type == ID_SO && !scene->texture.south)
		scene->texture.south = trimmed;
	else if (id_type == ID_WE && !scene->texture.west)
		scene->texture.west = trimmed;
	else if (id_type == ID_EA && !scene->texture.east)
		scene->texture.east = trimmed;
	else if (id_type == ID_F && !scene->floor.is_set)
		return (extract_rgb_color(scene, trimmed, id_type));
	else if (id_type == ID_C && !scene->ceiling.is_set)
		return (extract_rgb_color(scene, trimmed, id_type));
	else
	{
		free(trimmed);
		return (false);
	}
	return (true);
}

bool	check_and_fill_ids(int fd, t_scene *scene, int *total_ids)
{
	char			*line;
	unsigned int	id_type;
	int				i;

	while (*total_ids > 0)
	{
		line = gnl_non_empty(fd);
		if (!line)
			break ;
		id_type = is_id(line, &i);
		if (id_type == ID_INVALID || !fill_id(id_type, scene, line + i))
		{
			free(line);
			break ;
		}
		(*total_ids)--;
		free(line);
	}
	if (*total_ids)
		free_scene(scene);
	return (*total_ids == 0);
}
