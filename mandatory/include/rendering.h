/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 04:23:18 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/27 17:03:52 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "../../libs/MLX42/include/MLX42/MLX42.h"

int render(t_player *player, t_scene *scene, mlx_t *mlx);

#endif