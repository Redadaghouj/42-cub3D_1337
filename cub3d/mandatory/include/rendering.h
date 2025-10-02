/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboutahi <mboutahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 04:23:18 by redadgh           #+#    #+#             */
/*   Updated: 2025/10/02 14:18:54 by mboutahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include <MLX42/MLX42.h>

# define BASE_GUN_X 250
# define BASE_GUN_Y 420

# define RUN_FREQ 0.20f
# define RUN_AMP_X 5
# define RUN_AMP_Y 10

# define IDLE_FREQ 0.1f
# define IDLE_AMP_Y 2

typedef struct s_dda_data
{
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			side;
}				t_dda_data;

typedef struct s_texture_data
{
	int			tex_width;
	int			tex_height;
	int			tex_x;
	int			side;
	double		perp_wall_dist;
	int			draw_start;
	int			draw_end;
	int			line_height;
}				t_texture_data;

typedef struct s_wall_data
{
	t_player	*player;
	double		ray_dir_x;
	double		ray_dir_y;
	int			side;
	double		perp_wall_dist;
	int			draw_start;
	int			draw_end;
	int			line_height;
}				t_wall_data;

unsigned int	color_to_int(t_color c);
void			draw_floor_and_ceiling(mlx_image_t *img, t_scene *scene);
void			calculate_ray_direction(double x, t_player *player,
					t_wall_data *wall_data);
void			calculate_step_and_side_dist(t_player *player,
					t_wall_data *wall_data, t_dda_data *dda);
void			perform_dda(t_scene *scene, t_dda_data *dda);
void			close_doors(t_scene *scene, t_player *player);
void			interact_with_door(t_scene *scene, t_player *player,
					mlx_t *mlx);
void			calculate_wall_distance(t_player *player,
					t_wall_data *wall_data, t_dda_data *dda);
void			calculate_draw_bounds(double perp_wall_dist, int *draw_start,
					int *draw_end, int *line_height);
mlx_image_t		*select_texture(t_scene *scene, t_dda_data *dda,
					t_wall_data *wall_data);
void			calculate_texture_x(t_player *player, double ray_dir_x,
					double ray_dir_y, t_texture_data *tex_data);
void			draw_textured_wall_column(mlx_image_t *img, mlx_image_t *tex,
					int x, t_texture_data *tex_data);
void			draw_textured_wall(mlx_image_t *img, mlx_image_t *tex_img,
					int x, t_wall_data *wall_data);
void			draw_single_wall_column(mlx_image_t *img, t_scene *scene,
					t_player *player, int x);
void			draw_walls(mlx_image_t *img, t_scene *scene, t_player *player);
void			draw_gun(t_game_data *game_data, bool is_moving);
void			game_loop(void *param);
void			key_hook(mlx_key_data_t keydata, void *param);
int				render(t_player *player, t_scene *scene, mlx_t *mlx);
void			move_player_forward(t_player *player, char **map);
void			move_player_backward(t_player *player, char **map);
void			move_player_left(t_player *player, char **map);
void			move_player_right(t_player *player, char **map);
bool			can_move_to(char **map, double new_x, double new_y);
#endif
