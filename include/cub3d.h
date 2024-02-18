/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:15:49 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/18 10:12:27 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include "doxy.h"
# include "minimap.h"
# include "structs.h"

uint32_t		rgba_to_int(t_rgba color);
void			minimap_hook(void *tmp);

void			init_data_parser(t_data *data);
void			free_data(t_data *data);
void			free_textures_mlx(t_textures *textures);

// render.c
double			adjust_mirroring(double x, double width, double angle,
					char plane);
void			determine_plane_and_position(t_data *data, char *plane,
					double *wall_hit_position);
uint32_t		pixel_color(mlx_texture_t *texture, t_data *data,
					int wall_top_pixel);
void			render_wall(t_data *data);

char			*get_identifier_value(char *map_str, char *identifier);
int				load_textures(t_data *data);
void			free_exit(t_data *data);
void			key_pressed(t_data *data);
void			key_hook(void *tmp);
void			apply_movement(t_data *data, double move_x, double move_y);
void			rotate_player(double *orientation_angle_rd,
					enum e_rotation direction);
uint8_t			*render_pixel(mlx_image_t *image, uint32_t x, uint32_t y,
					int color);
float			normalize_angle(float angle);
void			calculate_and_render_rays(void *tmp);
int				update_steps_direction(float angle, float *step, char c);
int				check_collision_adjust_step(float angle, float *inter,
					float *step, char plane);
int				wall_hit(float x, float y, t_data *data);
float			find_x_collision(t_data *data, float angl);
float			find_y_collision(t_data *data, float angl);
void			game_hook(void *tmp);
void			init_player(t_data *data);
void			update_ray(t_data *data);
void			init_data(t_data *data);
void			free_exit_parser(t_data *data, char *error_message);
void			parser(int argc, char **argv, t_data *data);
void			init_player_original_orientation(t_data *data);
int				ray_direction(float angle, char plane);
int				reverse_bytes(int c);
int				is_wall(t_data *data, double x, double y);
mlx_texture_t	*texture_selection(t_data *data);
void			parse_file(char *file_path, char ***lines_arr);
void			print_lines_arr(char **lines_arr);
void			error_exit(char *error_msg);
void			*handle_ft_calloc(size_t *lines_arr_size, int fd);
void			*handle_ft_easy_realloc(char **lines_arr, size_t old_size,
					size_t new_size, int fd);
void			render_wall_and_background(t_data *data);

// BONUS

void			render_minimap(void *tmp);

#endif // CUB3D_H