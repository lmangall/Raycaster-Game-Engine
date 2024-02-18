/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doxy.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:03:48 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/18 18:29:21 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* functions_doxygen.h */

#ifndef DOXY_H
# define DOXY_H

# include "MLX42.h"
# include "libft.h"
# include "structs.h"
/**
 * @brief Adjusts a coordinate for mirroring based on specified conditions.
 *
 * This function adjusts the given coordinate 'x' for mirroring effects
 * based on the specified mirroring plane ('x' or 'y'), the mirroring angle,
 * and the direction
 * determined by the 'ray_direction' function. The adjustment ensures proper
 * mirroring behavior for rendering in a 2D space.
 *
 * @param x Original coordinate to be adjusted.
 * @param width Width of the mirroring region or surface.
 * @param angle Angle associated with the mirroring.
 * @param plane Mirroring plane ('x' or 'y') along which adjustment is applied.
 *
 * @return Adjusted coordinate after considering mirroring conditions.
 */
double	adjust_mirroring(double x, double width, double angle, char plane);

/**
 * @brief Get the value associated with a given identifier in a string.
 *
 * This function finds the position of the identifier in the input string
 * and retrieves the corresponding value. It skips spaces and returns the
 * identified value as a dynamically allocated string.
 *
 * @param map_str The input string containing the identifier and its value.
 * @param identifier The identifier whose value needs to be retrieved.
 *
 * @return A dynamically allocated string containing the value,
 * or NULL if
 * the identifier is not found or memory allocation fails. The caller is
 * responsible for freeing the allocated memory.
 */
char	*get_identifier_value(char *map_str, char *identifier);

int		load_textures(t_data *data);

/**
 * @brief Function to handle cleanup and exit the game.
 * @param data Pointer to the t_data structure.
 */
void	free_exit(t_data *data);

/**
 * @brief Function to handle key release events.
 * @param keydata Key data for the pressed key.
 * @param data Pointer to the t_data structure.
 */
void	ft_reles(mlx_key_data_t keydata, t_data *data);

void	key_pressed(t_data *data);
// void key_released(t_data *data);
void	key_hook(void *tmp);
void	apply_movement(t_data *data, double move_x, double move_y);

void	key_pressed(t_data *data);
// void key_released(t_data *data);
void	key_hook(void *tmp);
void	apply_movement(t_data *data, double move_x, double move_y);

/**
 * @brief Function to handle key press events.
 * @param keydata Key data for the pressed key.
 * @param tmp Extra param we can pass to the mlx_key hook that will be assigned
 * to the t_data.
 */
void	mlx_key(mlx_key_data_t keydata, void *tmp);

/**
 * @brief Function to rotate the player based on key input.
 * @param data Pointer to the t_data structure.
 * @param i Integer indicating the direction of rotation (1 for right, 0 for
 * left).
 */
void	rotate_player(double *orientation_angle_rd, enum e_rotation direction);

/**
 * @brief Function to move the player based on key input.
 * @param data Pointer to the t_data structure.
 * @param move_x Amount to move in the x-direction.
 * @param move_y Amount to move in the y-direction.
 */
void	move_player(t_data *data, double move_x, double move_y);

/**
 * @brief Function to handle player movement and rotation based on key input.
 * @param data Pointer to the t_data structure.
 * @param move_x Amount to move in the x-direction.
 * @param move_y Amount to move in the y-direction.
 */
void	hook(t_data *data, double move_x, double move_y);

/**
 * @brief Renders a pixel at the specified coordinates within an image.
 *


* @param image Pointer to the mlx_image_t structure representing the image.
 * @param x X-coordinate of the pixel to be rendered.
 * @param y Y-coordinate of the pixel to be rendered.
 * @param color The color value of the pixel to be rendered.

* @return a pointer to the start of the data within the image's pixel buffer.
* If the image is NULL, or if the coordinates are out of bounds, returns NULL.
 */

uint8_t	*render_pixel(mlx_image_t *image, uint32_t x, uint32_t y, int color);

/**
 * @brief Function to normalize an angle to be within the range [0, 2
 * PI).
 * @param angle Angle to be normalized.
 * @return Normalized angle.
 */
float	normalize_angle(float angle);

/**
 * @brief Renders the floor and ceiling of the scene.
 * @param mlx The main data structure.
 */
void	render_floor_ceiling(t_data *data);

/**
 * @brief Function to get the color of the wall based on its orientation.
 * @param data Pointer to the t_data structure.
 * @param colision_orientation Flag indicating wall orientation).
 * @return Color of the wall.
 */
int		get_color(t_data *data, int collision_orientation);

// void	raycasting(t_data *data);

/**
 * @brief Update the step direction (+/−) based on the given angle and axis.
 *
 * if we check x:
 * we check whether the angle is greater than 0 and less than π (180 degrees)
 * (=looking down).
 *
 * if we check y
 * we check if the ray is looking left
 *

	* if the angle is greater than π/2 (90 degrees) and less than 3π/2 (270 degrees
 *
 * @param angle The angle for which the step direction is updated.
 * @param step A pointer to the step value that will be updated.
 * @param c The axis character ('x' or 'y') indicating which axis to check.
 * @return Always returns 0.
 *
 * @note The function modifies the step value through the pointer.
 *
 * It adjusts the step based on the specified conditions in the unit circle.
 */
int		update_steps_direction(float angle, float *step, char c);

/**
 * @brief Function to check and update intersection points for horizontal or
 * vertical walls.
 * @param angle Angle of the ray.
 * @param inter Pointer to the intersection point, updated based on the
 * direction.
 * @param step Pointer to the step size, adjusted based on the direction.
 * @param is_horizon Flag indicating whether the intersection is for a
 * horizontal (1) or vertical (0) direction.
 * @return -1 if there is an intersection, 1 otherwise.
 */
int		check_collision_adjust_step(float angle, float *inter, float *step,
			char plane);

/**
 * @brief Function to check if a wall is hit based on coordinates.
 * @param x X-coordinate of the point.
 * @param y Y-coordinate of the point.
 * @param data Pointer to the t_data structure.
 * @return 1 if the wall is hit, 0 otherwise.
 */
int		wall_hit(float x, float y, t_data *data);

/**
 * @brief Function to get the horizontal intersection point of a wall.
 * @param data Pointer to the t_data structure.
 * @param angl Angle of the ray.
 * @return Horizontal intersection distance.
 */
float	find_x_collision(t_data *data, float angl);

/**
 * @brief Function to get the vertical intersection point
 * of a wall.
 * @param data Pointer to the t_data structure.
 * @param angl Angle of the ray.
 * @return Vertical intersection distance.
 */
float	find_y_collision(t_data *data, float angl);

/**
 * @brief Function to cast rays for rendering walls in the game.
 * @param data Pointer to the t_data structure.
 */
void	cast_rays(t_data *data);

/**
 * @brief Game loop function to handle player movement, ray casting, and
 * rendering.
 * @param tmp Pointer to the t_data structure.
 */
void	game_hook(void *tmp);

/**
 * @brief Function to initialize the player structure.
 * @param data The t_data structure.
 */
void	init_player(t_data *data);

/**
 * @brief Function to start the Cub3D game.
 * @param map Pointer to the game data structure.
 */
void	start_the_game(t_map *map, char *map_argv);

/**
 * @brief Main function to initialize the game and start the main loop.
 * @return 0 if the program runs successfully.
 */

/**
 * @brief Initializes the raycasting parameters.
 *
 * This function initializes the parameters used in the raycasting process. It
 * calculates the wall height, top and bottom pixels of the wall on the screen,
 * and sets the current texture for rendering. Additionally,
 * it adjusts the ray's distance to correct for fisheye distortion.
 *
 * @param mlx The main data structure.
 */
void	update_ray(t_data *data);

int		load_textures(t_data *data);

#endif // CUB3D_FUNCTIONS_DOXYGEN_H
