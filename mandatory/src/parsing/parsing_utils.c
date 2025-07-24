/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:16:35 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/24 03:30:17 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

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
}

bool	is_empty(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
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
		line = gnl(fd, 0);
		if (!line)
			return (NULL);
		else if (!is_empty(line))
			return (line);
		free(line);
	}
}
