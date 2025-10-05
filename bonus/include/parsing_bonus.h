/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 22:06:11 by redadgh           #+#    #+#             */
/*   Updated: 2025/10/05 18:20:09 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_BONUS_H
# define PARSING_BONUS_H

# include "../../assets/MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <stdbool.h>

# define TOTAL_IDS 7
# define IDENTIFIER_SKIP 2
# define ID_NORTH "NO "
# define ID_SOUTH "SO "
# define ID_WEST "WE "
# define ID_EAST "EA "
# define ID_DOOR "DO "
# define ID_FLOOR "F "
# define ID_CEIL "C "
# define ORIENTATION_CHARS "NSEW"
# define VALID_MAP_CHARS "NSEW0D"
# define TILE_CHARS "10D "
# define ERR_BAD_EXTENSION "Error\nBad extension\n"
# define ERR_SCENE_PATH "Error\nInvalid or inaccessible scene file path\n"
# define ERR_INVALID_ID "Error\nInvalid identifier in scene\n"
# define ERR_INVALID_MAP "Error\nInvalid map format\n"

typedef struct s_texture_paths
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*door;
}					t_texture_paths;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	char			orientation;
	double			angle;
}					t_player;

typedef struct s_color
{
	int				r;
	int				g;
	int				b;
	int				is_set;
}					t_color;

typedef struct s_scene
{
	t_texture_paths	texture;
	mlx_texture_t	*tex_north;
	mlx_texture_t	*tex_south;
	mlx_texture_t	*tex_west;
	mlx_texture_t	*tex_east;
	mlx_texture_t	*door_tex;
	mlx_texture_t	*gun_texture;
	mlx_texture_t	*hands[16];
	mlx_image_t		*last_hands;
	mlx_image_t		*gun_image;
	mlx_image_t		*img_north;
	mlx_image_t		*img_south;
	mlx_image_t		*img_west;
	mlx_image_t		*img_east;
	mlx_image_t		*door_img;
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
	ID_DO,
	ID_F,
	ID_C,
	ID_INVALID
}					t_id_type;

typedef enum e_direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
}					t_direction;

typedef struct s_game_data
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_scene			*scene;
	t_player		*player;
}					t_game_data;

/* PARSING */
bool	validate_scene(char *map_path, t_scene *scene,
			t_player *player);

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
void	set_player_direction(t_player *player, char direction);

/* PARSE_RGB */
bool	parse_rgb(t_scene *scene, char *line, unsigned int id_type);
int		create_rgb(int r, int g, int b);

/* PARSE_MAP_UTILS */
bool	is_in_bounds(char **map, int y, int x);
bool	is_open(char **map, int y, int x, t_direction dir);
char	**append_line_to_map(char **old_map, char *line,
			int old_len);
bool	door_between_walls(char **map);
void	init_player_data(char **map, t_player *player, int i, int j);

#endif