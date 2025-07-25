/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:58:29 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/25 05:28:20 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

char	**append_line_to_map(char **old_map, char *line, int old_len)
{
	int		i;
	char	**new_map;

	i = 0;
	new_map = (char **)malloc(sizeof (char *) * (old_len + 2));
	if (!new_map)
	{
		free_buffer(old_map);
		return (NULL);
	}
	while (i < old_len)
	{
		new_map[i] = old_map[i];
		i++;
	}
	new_map[i] = line;
	new_map[i + 1] = NULL;
	free(old_map);
	return (new_map);
}

bool	validate_content_and_init_player(char **map, t_player *player)
{
	int		i;
	int		j;
	bool	player_found;

	i = -1;
	player_found = false;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_strchr(ORIENTATIONS_CHARS, map[i][j]))
			{
				if (player_found)
					return (false);
				player->orientation = map[i][j];
				player->pos_y = i;
				player->pos_x = j;
				player_found = true;
			}
			else if (!ft_strchr(TILE_CHARS, map[i][j]))
				return (false);
		}
	}
	return (player_found);
}

bool	load_map(int fd, t_scene *scene)
{
	char	*line;
	int		len;

	len = 0;
	line = gnl_non_empty(fd);
	while (line)
	{
		scene->map = append_line_to_map(scene->map, line, len);
		if (!scene->map)
			return (false);
		line = get_next_line(fd);
		len++;
	}
	return (true);
}

bool	parse_map(int fd, t_scene *scene, t_player *player)
{
	if (!load_map(fd, scene))
		return (false);
	else if (!validate_content_and_init_player(scene->map, player))
		return (false);
	return (true);
}
