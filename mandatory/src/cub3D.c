/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:04:11 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/22 19:39:38 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		ft_putstr_fd(ERR_USAGE, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	else if (!validate_map(argv[1]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
