/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiers_handling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:28:47 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/23 21:29:41 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

unsigned int	is_id(char *line, int *i)
{
	*i = skip_leading_spaces(line);
	if (!ft_strncmp(line + *i, "NO ", 3) && (*i += 3))
		return (ID_NO);
	else if (!ft_strncmp(line + *i, "SO ", 3) && (*i += 3))
		return (ID_SO);
	else if (!ft_strncmp(line + *i, "WE ", 3) && (*i += 3))
		return (ID_WE);
	else if (!ft_strncmp(line + *i, "EA ", 3) && (*i += 3))
		return (ID_EA);
	else if (!ft_strncmp(line + *i, "F ", 2) && (*i += 2))
		return (ID_F);
	else if (!ft_strncmp(line + *i, "C ", 2) && (*i += 2))
		return (ID_C);
	else
		return (ID_INVALID);
}

bool	fill_id(unsigned int id_type, t_scene *scene, char *line)
{
	if (is_empty(line))
		return (false);
	else if (id_type == ID_NO && !scene->texture.north)
		scene->texture.north = ft_strtrim(line);
	else if (id_type == ID_SO && !scene->texture.south)
		scene->texture.south = ft_strtrim(line);
	else if (id_type == ID_WE && !scene->texture.west)
		scene->texture.west = ft_strtrim(line);
	else if (id_type == ID_EA && !scene->texture.east)
		scene->texture.east = ft_strtrim(line);
	else if (id_type == ID_F && !scene->floor.value)
		scene->floor.value = ft_strtrim(line);
	else if (id_type == ID_C && !scene->ceiling.value)
		scene->ceiling.value = ft_strtrim(line);
	else
		return (false);
	return (true);
}

bool	check_and_fill_ids(int fd, t_scene *scene, int *total_ids)
{
	char			*line;
	unsigned int	id_type;
	int 			i;

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
