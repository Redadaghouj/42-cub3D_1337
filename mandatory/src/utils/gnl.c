/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 19:56:08 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/22 19:56:22 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static int	fill_buffer(int fd, char *buffer, int *b_read, int *b_pos)
{
	*b_pos = 0;
	*b_read = read(fd, buffer, 1024);
	return (*b_read > 0);
}

char	*gnl(int fd, int i)
{
	static char	buffer[1024];
	char		line[70000];
	static int	b_pos;
	static int	b_read;

	i = 0;
	if (fd < 0)
		return (NULL);
	while (true)
	{
		if (b_pos >= b_read)
		{
			if (fill_buffer(fd, buffer, &b_read, &b_pos) <= 0)
				break ;
		}
		line[i++] = buffer[b_pos++];
		if (buffer[b_pos - 1] == '\n')
			break ;
	}
	line[i] = '\0';
	if (i == 0)
		return (NULL);
	return (ft_strdup(line));
}
