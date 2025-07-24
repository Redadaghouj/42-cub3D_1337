/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:54:37 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/24 04:21:19 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>
# include <fcntl.h>

# define TOTAL_IDS 6
# define ERR_BAD_EXTENSION "Error\nBad extension\n"
# define ERR_SCENE_PATH "Error\nInvalid or inaccessible scene file path\n"
# define ERR_INVALID_ID "Error\nInvalid identifier in scene\n"

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}				t_texture;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	int		is_set;
}				t_color;

typedef struct s_scene
{
	t_texture	texture;
	t_color		floor;
	t_color		ceiling;
	char		**map;
}				t_scene;

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
bool	validate_map(char *map_path, t_scene *scene);

/* PARSING UTILS */
bool	exit_with_error(char *error_msg);
bool	open_file(char *file_name, int *fd);
void	free_scene(t_scene *scene);
bool	is_empty(char *line);
char	*gnl_non_empty(int fd);

/* IDENTIFIERS_HANDLING */
bool	check_and_fill_ids(int fd, t_scene *scene, int *total_ids);

/* RGB_HANDLING */
bool	extract_rgb_color(t_scene *scene, char *line, unsigned int id_type);
int		create_rgb(int r, int g, int b);

#endif