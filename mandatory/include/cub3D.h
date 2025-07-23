/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:04:34 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/23 02:57:10 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# include "parsing.h"
# include "rendering.h"

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define ERR_USAGE "Error\nUsage: ./cub3D ./path_to_the_scene_file\n"


/* UTILS */
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *s);
char	*gnl(int fd, int i);

#endif