/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:04:11 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/29 19:44:20 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int argc, char *argv[])
{
	t_scene		scene;
	t_player	player;

	if (argc != EXPECTED_ARGC)
		return (exit_with_error(ERR_USAGE));
	else if (!validate_scene(argv[1], &scene, &player))
	{
		free_scene(&scene);
		return (EXIT_FAILURE);
	}
	free_scene(&scene);
	render();
	return (EXIT_SUCCESS);
}
