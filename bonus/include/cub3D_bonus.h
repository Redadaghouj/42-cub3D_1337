/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:04:34 by redadgh           #+#    #+#             */
/*   Updated: 2025/10/04 13:10:52 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <math.h>
# include <stddef.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "parsing_bonus.h"
# include "rendering_bonus.h"

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define ERR_USAGE "Error\nUsage: ./cub3D ./path_to_the_scene_file\n"

# define HEIGHT 800
# define WIDTH 1100
# define MOVE_SPEED 0.02
# define ROT_SPEED 0.02
# define HAND_SPEED 4
# define COLLISION_BUFFER 0.1

typedef struct s_mlxVar
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}				t_mlxVar;

/* UTILS */
size_t			ft_strlen(const char *s);
void			ft_putstr_fd(char *s, int fd);
int				ft_strcmp(char *s1, char *s2);
char			*ft_strdup(const char *s);
char			*get_next_line(int fd);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_substr(const char *s, unsigned int start, size_t len);
char			*ft_strtrim(char *line);
int				skip_leading_spaces(char *line); // UTILS -> ft_strtrim
char			**ft_split(char const *s, char c);
void			*free_buffer(char **buffer); // UTILS -> ft_split
int				ft_atoi(const char *nptr);
int				ft_isdigit(int c);
char			*ft_strchr(const char *s, int c);
int				handle_movement_keys(mlx_t *mlx, t_player *player, char **map);
// void	interact_with_door(t_scene *scene, t_player *player);

#endif