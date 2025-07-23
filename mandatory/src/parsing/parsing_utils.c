/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:16:35 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/23 02:26:08 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

bool	exit_with_error(char *error_msg)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	return (false);
}
