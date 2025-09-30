/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:58:29 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/26 21:58:30 by redadgh          ###   ########.fr       */
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

bool	is_in_bounds(char **map, int y, int x)
{
	if (y < 0 || x < 0 || !map[y])
		return (false);
	if ((size_t)x >= ft_strlen(map[y]))
		return (false);
	return (true);
}

bool	is_open(char **map, int y, int x, t_direction dir)
{
	if (dir == UP)
		return (!is_in_bounds(map, y - 1, x) || map[y - 1][x] == ' ');
	else if (dir == DOWN)
		return (!is_in_bounds(map, y + 1, x) || map[y + 1][x] == ' ');
	else if (dir == LEFT)
		return (!is_in_bounds(map, y, x - 1) || map[y][x - 1] == ' ');
	else if (dir == RIGHT)
		return (!is_in_bounds(map, y, x + 1) || map[y][x + 1] == ' ');
	else
		return (false);
}
