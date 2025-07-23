/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redadgh <redadgh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:54:37 by redadgh           #+#    #+#             */
/*   Updated: 2025/07/23 02:57:27 by redadgh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>
# include <fcntl.h>

# define ERR_BAD_EXTENSION "Error\nBad extension\n"
# define ERR_SCENE_PATH "Error\nInvalid or inaccessible scene file path\n"
# define ERR_INVALID_ID "Error\nInvalid or unexpected identifier in scene file\n"

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}				t_texture;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_scene
{
	t_texture	texture;
	t_color		floor;
	t_color		ceiling;
	char		**map;
}				t_scene;

/* PARSING */
bool	validate_map(char *map_path);

/* PARSING UTILS */
bool	exit_with_error(char *error_msg);

#endif