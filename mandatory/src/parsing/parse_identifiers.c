/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifiers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 21:28:47 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/29 19:42:37 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

unsigned int	is_id(char *line, int *i)
{
	*i = skip_leading_spaces(line);
	if (!ft_strncmp(line + *i, ID_NORTH, ft_strlen(ID_NORTH)))
		return (ID_NO);
	else if (!ft_strncmp(line + *i, ID_SOUTH, ft_strlen(ID_SOUTH)))
		return (ID_SO);
	else if (!ft_strncmp(line + *i, ID_WEST, ft_strlen(ID_WEST)))
		return (ID_WE);
	else if (!ft_strncmp(line + *i, ID_EAST, ft_strlen(ID_EAST)))
		return (ID_EA);
	else if (!ft_strncmp(line + *i, ID_FLOOR, ft_strlen(ID_FLOOR)))
		return (ID_F);
	else if (!ft_strncmp(line + *i, ID_CEIL, ft_strlen(ID_CEIL)))
		return (ID_C);
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
		return (parse_rgb(scene, trimmed, id_type));
	else if (id_type == ID_C && !scene->ceiling.is_set)
		return (parse_rgb(scene, trimmed, id_type));
	else
	{
		free(trimmed);
		return (false);
	}
	return (true);
}

bool	parse_identifiers(int fd, t_scene *scene)
{
	char			*line;
	unsigned int	id_type;
	int				total_ids;
	int				i;

	total_ids = TOTAL_IDS;
	while (total_ids > 0)
	{
		line = gnl_non_empty(fd);
		if (!line)
			break ;
		id_type = is_id(line, &i);
		i += ID_LENGTH;
		if (id_type == ID_INVALID || !fill_id(id_type, scene, line + i))
		{
			free(line);
			break ;
		}
		total_ids--;
		free(line);
	}
	return (total_ids == 0);
}
