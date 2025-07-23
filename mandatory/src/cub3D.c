/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:04:11 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/23 03:00:26 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (exit_with_error(ERR_USAGE));
	else if (!validate_map(argv[1]))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
