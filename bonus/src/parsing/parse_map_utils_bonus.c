/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 19:58:29 by redadgh           #+#    #+#             */
/*   Updated: 2025/10/05 18:17:24 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

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

void	init_player_data(char **map, t_player *player, int i, int j)
{
	player->orientation = map[i][j];
	player->pos_y = i + 0.5;
	player->pos_x = j + 0.5;
	set_player_direction(player, map[i][j]);
}

bool	door_between_walls(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'D')
			{
				if ((map[i + 1][j] != '1' && map[i - 1][j] != '1') && map[i][j
					+ 1] != '1' && map[i][j - 1] != '1')
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}
