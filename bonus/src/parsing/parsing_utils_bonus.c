/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdaghouj <mdaghouj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:16:35 by redadgh           #+#    #+#             */
/*   Updated: 2025/10/06 12:31:01 by mdaghouj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D_bonus.h"

bool	exit_with_error(char *error_msg)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	return (false);
}

bool	open_file(char *file_name, int *fd)
{
	*fd = open(file_name, O_RDONLY);
	if (*fd < 0)
		return (false);
	return (true);
}

void	free_scene(t_scene *scene)
{
	if (scene->texture.north)
		free(scene->texture.north);
	if (scene->texture.south)
		free(scene->texture.south);
	if (scene->texture.west)
		free(scene->texture.west);
	if (scene->texture.east)
		free(scene->texture.east);
	if (scene->texture.door)
		free(scene->texture.door);
	if (scene->map)
		free_buffer(scene->map);
}

bool	is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

char	*gnl_non_empty(int fd)
{
	char	*line;

	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			return (NULL);
		else if (!is_empty(line))
			return (line);
		free(line);
	}
}
