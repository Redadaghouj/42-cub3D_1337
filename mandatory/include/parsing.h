/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:54:37 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/25 06:00:05 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>
# include <fcntl.h>

# define TOTAL_IDS 6
# define ID_NORTH "NO "
# define ID_SOUTH "SO "
# define ID_WEST "WE "
# define ID_EAST "EA "
# define ID_FLOOR "F "
# define ID_CEIL "C "
# define ORIENTATIONS_CHARS "NSEW"
# define TILE_CHARS "10 "
# define ERR_BAD_EXTENSION "Error\nBad extension\n"
# define ERR_SCENE_PATH "Error\nInvalid or inaccessible scene file path\n"
# define ERR_INVALID_ID "Error\nInvalid identifier in scene\n"
# define ERR_INVALID_MAP "Error\nInvalid map format\n"

typedef struct s_texture_paths
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}				t_texture_paths;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		is_set;
}				t_color;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	char	orientation;			
}				t_player;

typedef struct s_scene
{
	t_texture_paths	texture;
	t_color			floor;
	t_color			ceiling;
	char			**map;
}					t_scene;

typedef enum e_identifier_type
{
	ID_NO,
	ID_SO,
	ID_WE,
	ID_EA,
	ID_F,
	ID_C,
	ID_INVALID
}	t_id_type;

/* PARSING */
bool	validate_scene(char *map_path, t_scene *scene, t_player *player);

/* PARSING UTILS */
bool	exit_with_error(char *error_msg);
bool	open_file(char *file_name, int *fd);
void	free_scene(t_scene *scene);
bool	is_empty(char *line);
char	*gnl_non_empty(int fd);

/* PARSE_IDENTIFIERS */
bool	parse_identifiers(int fd, t_scene *scene, int *total_ids);

/* PARSE_MAP */
bool	parse_map(int fd, t_scene *scene, t_player *player);

/* PARSE_RGB */
bool	parse_rgb(t_scene *scene, char *line, unsigned int id_type);
int		create_rgb(int r, int g, int b);

#endif