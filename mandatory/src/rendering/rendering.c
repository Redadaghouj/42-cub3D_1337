/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 04:19:39 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/27 17:00:11 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	render(void)
{
	mlx_t *mlx = mlx_init(200, 100, "MLX42 Window", true);
	if (!mlx)
	{
		fprintf(stderr, "Failed to initialize MLX\n");
		return (EXIT_FAILURE);
	}

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
