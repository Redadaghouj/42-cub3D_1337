/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 04:16:20 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/22 04:19:22 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "../../include/cub3D.h"

void	cast_ray(t_player *p, char **map, int x)
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;

	// 1. calculate ray direction based on camera plane and screen x
	camera_x = 2 * x / (double)WIDTH - 1; // x goes from -1 to 1
	ray_dir_x = p->dir_x + p->plane_x * camera_x;
	ray_dir_y = p->dir_y + p->plane_y * camera_x;

	// 2. where in the map the ray starts (player's current tile)
	int map_x = (int)p->pos_x;
	int map_y = (int)p->pos_y;

	// 3. length of ray to next x or y side
	double delta_dist_x = fabs(1 / ray_dir_x);
	double delta_dist_y = fabs(1 / ray_dir_y);

	// 4. setup step and initial side distance
	int step_x;
	int step_y;
	double side_dist_x;
	double side_dist_y;

	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (p->pos_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - p->pos_x) * delta_dist_x;
	}

	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (p->pos_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - p->pos_y) * delta_dist_y;
	}

	// 5. Perform DDA
	int hit = 0;
	while (!hit)
	{
		// step in the direction of smallest distance
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
		}

		// check if we hit a wall
		if (map[map_y][map_x] == '1')
			hit = 1;
	}

	// 6. Print the hit
	printf("Ray %d hit a wall at map tile (%d, %d)\n", x, map_x, map_y);
}

