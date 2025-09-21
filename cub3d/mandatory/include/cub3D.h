/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 14:04:34 by redadgh           #+#    #+#             */
/*   Updated: 2025/09/19 12:50:03 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stddef.h>

# include "parsing.h"
# include "rendering.h"

# define EXIT_FAILURE 1
# define EXIT_SUCCESS 0
# define ERR_USAGE "Error\nUsage: ./cub3D ./path_to_the_scene_file\n"

# define HEIGHT 800
# define WIDTH 800
#define MOVE_SPEED 0.05
#define ROT_SPEED 0.05
#define COLLISION_BUFFER 0.1
typedef struct s_mlxVar
{
	mlx_t			*mlx;
	mlx_image_t		*img;
}	t_mlxVar;

typedef struct s_dda_data
{
	int map_x;
	int map_y;
	double side_dist_x;
	double side_dist_y;
	double delta_dist_x;
	double delta_dist_y;
	double perp_wall_dist;
	int step_x;
	int step_y;
	int side;
} t_dda_data;

typedef struct s_texture_data
{
	int tex_width;
	int tex_height;
	int tex_x;
	int side;
	double perp_wall_dist;
	int draw_start;
	int draw_end;
	int line_height;
} t_texture_data;

typedef struct s_wall_data
{
	t_player *player;
	double ray_dir_x;
	double ray_dir_y;
	int side;
	double perp_wall_dist;
	int draw_start;
	int draw_end;
	int line_height;
} t_wall_data;
/* UTILS */
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(const char *s);
char	*get_next_line(int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strtrim(char *line);
int		skip_leading_spaces(char *line); // UTILS -> ft_strtrim
char	**ft_split(char const *s, char c);
void	*free_buffer(char **buffer); // UTILS -> ft_split
int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
char	*ft_strchr(const char *s, int c);
void 	handle_movement_keys(mlx_t *mlx, t_player *player, char **map);


#endif