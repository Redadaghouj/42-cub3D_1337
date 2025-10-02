/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 03:05:03 by redadgh           #+#    #+#             */
/*   Updated: 2025/10/02 22:07:12 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

int	create_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

bool	clean_exit(char **buffer, char *line, bool exit_status)
{
	free_buffer(buffer);
	free(line);
	return (exit_status);
}

void	store_rgb(unsigned int id_type, t_scene *scene, int rgb[])
{
	if (id_type == ID_F)
		scene->floor = (t_color){rgb[0], rgb[1], rgb[2], 1};
	else
		scene->ceiling = (t_color){rgb[0], rgb[1], rgb[2], 1};
}

bool	is_valid_rgb_format(char *line)
{
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
		{
			while (ft_isdigit(line[i]))
				i++;
			if (line[i] && line[i] != ',')
				return (false);
			else if (line[i] == ',')
			{
				comma_count++;
				i++;
			}
		}
		else
			return (false);
	}
	return (comma_count == 2);
}

bool	parse_rgb(t_scene *scene, char *line, unsigned int id_type)
{
	char	**buffer;
	int		i;
	int		rgb[3];

	i = 0;
	if (is_valid_rgb_format(line))
	{
		buffer = ft_split(line, ',');
		if (!buffer)
			return (false);
		while (buffer[i] != NULL)
		{
			rgb[i] = ft_atoi(buffer[i]);
			if (rgb[i] < 0 || rgb[i] > 255)
				return (clean_exit(buffer, line, false));
			i++;
		}
		store_rgb(id_type, scene, rgb);
		return (clean_exit(buffer, line, true));
	}
	free(line);
	return (false);
}
