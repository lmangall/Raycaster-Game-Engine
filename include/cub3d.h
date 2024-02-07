#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42.h"
# include "doxy.h"
# include "structs.h"

// render.c
double			adjust_mirroring(double x, double width, double angle,
					char plane);
void			determine_plane_and_position(t_data *data, char *plane,
					double *wall_hit_position);
uint32_t		pixel_color(mlx_texture_t *texture, t_data *data,
					int higher_pixel);
void			render_wall(t_data *data);
//
char			*get_identifier_value(char *map_str, char *identifier);
int				load_textures(t_data *data);
void			free_exit(t_data *data);
void			ft_reles(mlx_key_data_t keydata, t_data *data);
void			key_pressed(t_data *data);
void			key_hook(void *tmp);
void			apply_movement(t_data *data, double move_x, double move_y);
void			rotate_player(double *orientation_angle_rd,
					enum e_rotation direction);
void			move_player(t_data *data, double move_x, double move_y);
void			hook(t_data *data, double move_x, double move_y);
void			render_pixel(t_data *data, int y, int color);
float			normalize_angle(float angle);
void			render_floor_ceiling(t_data *data);
int				get_color(t_data *data, int collision_orientation);
void			draw_wall(t_data *data, int ray, int higher_pixel,
					int lower_pixel);
void			raycasting(t_data *data);
int				update_steps_direction(float angle, float *step, char c);
int				check_collision_adjust_step(float angle, float *inter,
					float *step, char plane);
int				wall_hit(float x, float y, t_data *data);
float			find_x_collision(t_data *data, float angl);
float			find_y_collision(t_data *data, float angl);
void			cast_rays(t_data *data);
void			game_hook(void *tmp);
void			init_player(t_data *data);
void			start_the_game(t_map *map, char *map_argv);
void			update_ray(t_data *data);
void			init_data(t_data *data);
void			render_background(mlx_t *mlx, t_rgba c, t_rgba f);
void			free_exit_parser(t_data *data, char *error_message);
void			parser(int argc, char **argv, t_data *data);
void			init_player_original_orientation(t_data *data);
int				ray_direction(float angle, char plane);
int				reverse_bytes(int c);
int				is_wall(t_data *data, double x, double y);
mlx_texture_t	*texture_selection(t_data *data);
void			init(t_map *map, char *map_argv);
void			parse_map(char *argv, t_map *map);
void			parse_file(char *file_path, char ***lines_arr);
void			print_lines_arr(char **lines_arr);
void			error_exit(char *error_msg);
void			*handle_ft_calloc(size_t *lines_arr_size, int fd);
void			*handle_ft_easy_realloc(char **lines_arr, size_t old_size,
					size_t new_size, int fd);
void			check_file(char *map_file);
void			render_wall(t_data *data);

#endif // CUB3D_H