/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:58:29 by redadgh           #+#    #+#             */
/*   Updated: 2025/10/05 18:17:15 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"
#include <stdbool.h>

bool	load_map(int fd, t_scene *scene)
{
	char	*line;
	int		len;

	len = 0;
	line = gnl_non_empty(fd);
	if (!line)
		return (false);
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

void	set_player_direction(t_player *player, char direction)
{
	if (direction == 'N')
		player->angle = -M_PI / 2;
	else if (direction == 'S')
		player->angle = M_PI / 2;
	else if (direction == 'E')
		player->angle = 0;
	else if (direction == 'W')
		player->angle = M_PI;
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->plane_x = sin(player->angle) * 0.66;
	player->plane_y = -cos(player->angle) * 0.66;
}

bool	check_elems_player(char **map, t_player *player, bool seen_player)
{
	int	i;
	int	j;
	int	seen_door;

	i = -1;
	seen_door = false;
	while (map[++i])
	{
		if (map[i][0] == '\0')
			return (false);
		j = -1;
		while (map[i][++j])
		{
			if (ft_strchr(ORIENTATION_CHARS, map[i][j]))
			{
				if (seen_player)
					return (false);
				init_player_data(map, player, i, j);
				seen_player = true;
			}
			else if (!ft_strchr(TILE_CHARS, map[i][j]))
				return (false);
		}
	}
	return (seen_player);
}

bool	is_map_enclosed(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr(VALID_MAP_CHARS, map[i][j]))
			{
				if (is_open(map, i, j, UP))
					return (false);
				if (is_open(map, i, j, DOWN))
					return (false);
				if (is_open(map, i, j, RIGHT))
					return (false);
				if (is_open(map, i, j, LEFT))
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	parse_map(int fd, t_scene *scene, t_player *player)
{
	if (!load_map(fd, scene))
		return (false);
	else if (!check_elems_player(scene->map, player, false))
		return (false);
	else if (!is_map_enclosed(scene->map))
		return (false);
	else if (!door_between_walls(scene->map))
		return (false);
	return (true);
}
