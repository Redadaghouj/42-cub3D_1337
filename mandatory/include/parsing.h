/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:54:37 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/27 02:59:28 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>
# include <fcntl.h>

# define TOTAL_IDS 6
# define IDENTIFIER_SKIP 3
# define ID_NORTH "NO "
# define ID_SOUTH "SO "
# define ID_WEST "WE "
# define ID_EAST "EA "
# define ID_FLOOR "F "
# define ID_CEIL "C "
# define ORIENTATION_CHARS "NSEW"
# define VALID_MAP_CHARS "NSEW0"
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

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	char	orientation;			
}				t_player;

typedef struct s_scene
{
	t_texture_paths	texture;
	int			floor;
	int			ceiling;
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

typedef enum e_direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}	t_direction;


# define COLOR_WHITE   0xFFFFFFFF
# define COLOR_BLACK   0x000000FF
# define COLOR_RED     0xFF0000FF
# define COLOR_GREEN   0x00FF00FF
# define COLOR_BLUE    0x0000FFFF
# define COLOR_BROWN   0x8B4513FF
# define COLOR_BLUE_SKY 0x87CEEBFF 

/* PARSING */
bool	validate_scene(char *map_path, t_scene *scene, t_player *player);

/* PARSING_UTILS */
bool	exit_with_error(char *error_msg);
bool	open_file(char *file_name, int *fd);
void	free_scene(t_scene *scene);
bool	is_empty(char *line);
char	*gnl_non_empty(int fd);

/* PARSE_IDENTIFIERS */
bool	parse_identifiers(int fd, t_scene *scene);

/* PARSE_MAP */
bool	parse_map(int fd, t_scene *scene, t_player *player);

/* PARSE_RGB */
bool	parse_rgb(t_scene *scene, char *line, unsigned int id_type);
int		create_rgb(int r, int g, int b);

/* PARSE_MAP_UTILS */
bool	is_in_bounds(char **map, int y, int x);
bool	is_open(char **map, int y, int x, t_direction dir);
char	**append_line_to_map(char **old_map, char *line, int old_len);

#endif