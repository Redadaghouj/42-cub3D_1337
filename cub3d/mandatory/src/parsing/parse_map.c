/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:58:29 by redadgh           #+#    #+#             */
/*   Updated: 2025/10/02 13:22:35 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

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

void set_player_direction(t_player *player, char direction)
{
	if (direction == 'N')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
		player->plane_x = 0.66;
		player->plane_y = 0.0;
	}
	else if (direction == 'S') 
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
		player->plane_x = -0.66;
		player->plane_y = 0.0;
	}
	else if (direction == 'E') 
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = 0.66;
	}
	else if (direction == 'W') 
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = -0.66;
	}
	else 
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
		player->plane_x = 0.66;
		player->plane_y = 0.0;
	}
	
	printf("Set player direction '%c': dir(%.2f,%.2f) plane(%.2f,%.2f)\n", 
		direction, player->dir_x, player->dir_y, player->plane_x, player->plane_y);
}

bool	check_elems_player(char **map, t_player *player, bool seen_player)
{
	int		i;
	int		j;

	i = -1;
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
				player->orientation = map[i][j];
				player->pos_y = i + 0.5; 
				player->pos_x = j + 0.5; 

				set_player_direction(player, map[i][j]);
				
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
	return (true);
}
