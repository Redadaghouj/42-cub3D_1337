/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:16:35 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/22 20:02:38 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

bool check_extension(char *map_path)
{
	char	*ext;
	int		idx;

	ext = ".cub";
	idx = ft_strlen(map_path) - 4;
	if (ft_strcmp(map_path + idx, ext) != 0)
		return (false);
	return (true);
}

bool	validate_map(char *map_path)
{
	if (!check_extension(map_path))
	{
		ft_putstr_fd(ERR_BAD_EXTENSION, STDERR_FILENO);
		return (false);
	}
	return (true);
}
