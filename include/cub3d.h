#ifndef CUB3D_H
# define CUB3D_H

/**
 * @file cub3d.h
 * @brief Header file for the Cub3D game.
 */

# include "MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>

# define WINDOW_WIDTH 1900
# define WINDOW_HEIGHT 1000
# define TILE_SIZE 30
# define FOV 60
# define PLAYER_ROTATION_SPEED 0.045
# define PLAYER_TRANSLATION_SPEED 4
# define ERROR_OPENING_FILE "File not found or corrupted."
# define SUCCESS 0
# define FAILURE 1

typedef enum e_mode
{
	PARSE_ONLY,
	FULL_EXPERIENCE
}						t_mode;

/**

	* @brief enum to represent the two possible values of the elements in the t_map_eements struct and of the player.
 */

typedef enum e_status
{
	NOT_FOUND,
	FOUND
}						t_status;

/**

	* @brief Structure to  keep track if the elements of the map have been found or not.
 */

typedef struct s_map_elements
{
	t_status			no;
	t_status			so;
	t_status			we;
	t_status			ea;
	t_status			c;
	t_status			f;
}						t_map_elements;

/**
 * @brief Structure to represent a color in RGBA format.
 */

typedef struct s_rgba
{
	int r; // Red component, usually in the range [0, 255]
	int g; // Green component, usually in the range [0, 255]
	int b; // Blue component, usually in the range [0, 255]
	int a; // Alpha component for transparency, usually in the range [0, 255]
}						t_rgba;

/**
 * @brief Structure to hold the paths to the textures.
 */

typedef struct s_textures_paths
{
	char				*north;
	char				*south;
	char				*west;
	char				*east;
}						t_textures_paths;

/**
 * @brief Struct to represent all the information we got from the map file.
 */
typedef struct s_map
{
	char **grid;             /**< 2D array representing the map. */
	int p_x;                 /**< Player x position in the map in tiles. */
	int p_y;                 /**< Player y position in the map in tiles. */
	char player_orientation; /**< Player orientation. */
	t_status player_found;   /**< Flag if the player has been found. */
	int width;               /**< Map width in tiles. */
	int height;              /**< Map height in tiles. */
	t_rgba c;                /**< Ceiling color. */
	t_rgba f;                /**< Floor color. */
	t_textures_paths	*textures_paths;
}						t_map;

/**
 * @brief Structure to save the path to textures.
 */
typedef struct s_textures
{
	mlx_texture_t		*north;
	mlx_texture_t		*south;
	mlx_texture_t		*west;
	mlx_texture_t		*east;
	mlx_texture_t		*floor;
	mlx_texture_t		*ceiling;
}						t_textures;

/**
 * @brief Enum for player rotation states.
 *
 * This enum defines possible states of rotation for the player.
 *
 * @param R_NONE No rotation.
 * @param R_RIGHT Rotate to the right.
 * @param R_LEFT Rotate to the left.
 */
typedef enum e_rotation
{
	R_NONE = 0,
	R_RIGHT = 1,
	R_LEFT = 2
}						t_rotation;

/**
 * @brief Enum for player's lateral movement direction.
 *
 * This enum defines possible lateral movement directions for the player,
 * relative to their current orientation.
 *
 * @param L_NONE No lateral movement.
 * @param L_RIGHT Move to the right relative to player's orientation.
 * @param L_LEFT Move to the left relative to player's orientation.
 */
typedef enum t_lateral_move
{
	L_NONE = 0,
	L_RIGHT = 1,
	L_LEFT = 2
}						t_lateral_move;

/**
 * @enum t_longitudinal_move
 * @brief Enum for player's longitudinal (forward and backward) movement
 * direction.
 *
 * This enum defines the possible directions for the player's longitudinal
 * movement, indicating moving forward, moving backward, or not moving along
 * this axis.
 */
typedef enum t_longitudinal_move
{
	NONE = 0,    /**< No longitudinal (forward/backward) movement. */
	FORWARD = 1, /**< Move forward. */
	BACKWARD = 2 /**< Move backward. */
}						t_longitudinal_move;

/**
 * @brief Structure to represent the player in the game.
 */
typedef struct s_player
{
	int x_pos_px;                /**< Player x position in pixels. */
	int y_pos_px;                /**< Player y position in pixels. */
	double orientation_angle_rd; /**< Player angle. */
	float fov_rd;                /**< Field of view in radians. */
	int					rotation_speed;
	int					translation_speed;
	t_rotation rotation;                   /**< Rotation direction: none, right,
        left. */
	t_lateral_move lateral_move;           /**< Lateral movement direction. */
	t_longitudinal_move longitudinal_move; /**< Longitudinal (forward/backward)
												movement direction. */
}						t_player;

/**
 * @enum e_wall_collision
 * @brief Enum for the type of wall collision.
 */
typedef enum e_wall_collision
{
	NO_COLLISION = 0, /**< No wall collision. */
	HORIZONTAL = 1,   /**< Horizontal wall collision. */
	VERTICAL = 2      /**< Vertical wall collision. */
}						t_wall_collision;

/**
 * @brief Structure representing a ray in the game.
 *
 * This structure contains information about a ray, including its column index,
 * angle, intersection points, distance to the wall, and wall orientation.
 *
 * @param column_index Index of the ray's column.
 * @param ray_angle Angle of the ray.
 * @param horizontal_x X-coordinate of horizontal intersection point.
 * @param horizontal_y Y-coordinate of horizontal intersection point.
 * @param vertical_x X-coordinate of vertical intersection point.
 * @param vertical_y Y-coordinate of vertical intersection point.
 * @param distance Distance to the wall.

	* @param wall_orientation Flag indicating wall orientation (horizontal/vertical).
 */
typedef struct s_ray
{
	double angle_rd; /**< Ray angle. */
	double				length;
	t_wall_collision	wall_collision_orientation;
	double				horizontal_x;
	double				horizontal_y;
	double				vertical_x;
	double				vertical_y;
	int					wall_orientation;
	int					is_wall;
	int					screen_x;
	mlx_texture_t		*current_texture;
	int					wall_h;
	int					higher_pixel;
	int					lower_pixel;

}						t_ray;

/**
 * @brief Structure to hold MLX-related elements and game data.
 */
typedef struct s_data
{
	char *argv;           /**< Pointer to the map file. */
	mlx_image_t *img;     /**< Pointer to the image. */
	mlx_t *mlx;           /**< Pointer to the MLX instance. */
	t_ray *ray;           /**< Pointer to the ray structure. */
	t_map *map;           /**< Pointer to the map structure. */
	t_player *player;     /**< Pointer to the player structure. */
	t_textures *textures; /**< Pointer to the textures structure. */
							/**< Pointer to the texture paths structure. */
}						t_data;

mlx_texture_t			*texture_selection(t_data *data);
void					init(t_map *map, char *map_argv);
int						is_wall(t_data *data, double x, double y);
void					init_data(t_data *data);

// render
uint32_t				pixel_color(mlx_texture_t *texture, t_data *data,
							int higher_pixel);
void					render_wall(t_data *data);
int						reverse_bytes(int c);

// PARSER:
void					check_file(char *map_file);
void					process_map(char **lines_arr, t_data *data);
void					parse_map(char *argv, t_map *map);
char					**parse_file(char *file_path);
void					print_lines_arr(char **lines_arr);
void					parser(int argc, char **argv, t_data *data);
char					**parse_file(char *file_path);
void					error_exit(char *error_msg, t_data *data);
void					*handle_ft_calloc(size_t *lines_arr_size, int fd);
void					*handle_ft_easy_realloc(char **lines_arr,
							size_t old_size, size_t new_size, int fd);
void					free_lines_arr_and_exit(char **lines_arr);
void					check_file(char *map_file);
void					process_map(char **lines_arr, t_data *data);
void					free_exit_parser(t_data *data);

void	render_background(mlx_t *mlx, t_rgba c, t_rgba f); //, t_rgb color)

// OLD PARSER:
char					*cub_to_str(char *map);

// TEXTURES:     UPDATE DOXY
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
		or NULL if
	* the identifier is not found or memory allocation fails. The caller is
	* responsible for freeing the allocated memory.
	*/
char					*get_identifier_value(char *map_str, char *identifier);

int						load_textures(t_data *data);

/**
 * @brief Function to handle cleanup and exit the game.
 * @param data Pointer to the t_data structure.
 */
void					free_exit(t_data *data);

/**
 * @brief Function to handle key release events.
 * @param keydata Key data for the pressed key.
 * @param data Pointer to the t_data structure.
 */
void					ft_reles(mlx_key_data_t keydata, t_data *data);

void					key_pressed(t_data *data);
// void	key_released(t_data *data);
void					key_hook(void *tmp);
void					apply_movement(t_data *data, double move_x,
							double move_y);

/**
 * @brief Function to handle key press events.
 * @param keydata Key data for the pressed key.
 * @param tmp Extra param we can pass to the mlx_key hook that will be assigned
 * to the t_data.
 */
void					mlx_key(mlx_key_data_t keydata, void *tmp);

/**
 * @brief Function to rotate the player based on key input.
 * @param data Pointer to the t_data structure.
 * @param i Integer indicating the direction of rotation (1 for right, 0 for
 * left).
 */
void					rotate_player(double *orientation_angle_rd,
							enum e_rotation direction);

/**
 * @brief Function to move the player based on key input.
 * @param data Pointer to the t_data structure.
 * @param move_x Amount to move in the x-direction.
 * @param move_y Amount to move in the y-direction.
 */
void					move_player(t_data *data, double move_x, double move_y);

/**
 * @brief Function to handle player movement and rotation based on key input.
 * @param data Pointer to the t_data structure.
 * @param move_x Amount to move in the x-direction.
 * @param move_y Amount to move in the y-direction.
 */
void					hook(t_data *data, double move_x, double move_y);

/**
 * @brief Function to put a pixel on the screen.
 * @param data Pointer to the t_data structure.
 * @param x X-coordinate of the pixel.
 * @param y Y-coordinate of the pixel.
 * @param color Color of the pixel.
 */
void					render_pixel(t_data *data, int y, int color);

/**
 * @brief Function to normalize an angle to be within the range [0, 2 * PI).
 * @param angle Angle to be normalized.
 * @return Normalized angle.
 */
float					normalize_angle(float angle);

/**
 * @brief Renders the floor and ceiling of the scene.
 * @param mlx The main data structure.
 */
void					render_floor_ceiling(t_data *data);

/**
 * @brief Function to get the color of the wall based on its orientation.
 * @param data Pointer to the t_data structure.
 * @param colision_orientation Flag indicating wall orientation).
 * @return Color of the wall.
 */
int						get_color(t_data *data, int collision_orientation);

/**
 * @brief Function to draw a wall on the screen.
 * @param data Pointer to the t_data structure.
 * @param ray Ray representing the current column.
 * @param higher_pixel Top pixel of the wall.
 * @param lower_pixel Bottom pixel of the wall.
 */
void					draw_wall(t_data *data, int ray, int higher_pixel,
							int lower_pixel);

/**
 * @brief Function to cast rays and render the walls in the game.
 * @param data Pointer to the t_data structure.
 */
void					raycasting(t_data *data);

/**
 * @brief Update the step direction (+/−) based on the given angle and axis.
 *
 * if we check x:
 * we check whether the angle is greater than 0 and less than π (180 degrees)
 * (=looking down).
 *
 * if we check y
 * we check if  the ray is looking left

	* if the angle is greater than π/2 (90 degrees) and less than 3π/2 (270 degrees))
 *
 * @param angle The angle for which the step direction is updated.
 * @param step A pointer to the step value that will be updated.
 * @param c The axis character ('x' or 'y') indicating which axis to check.
 * @return Always returns 0.
 *
 * @note The function modifies the step value through the pointer.

	*       It adjusts the step based on the specified conditions in the unit circle.
 */
int						update_steps_direction(float angle, float *step,
							char c);

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
int						check_collision_adjust_step(float angle, float *inter,
							float *step, char plane);

/**
 * @brief Function to check if a wall is hit based on coordinates.
 * @param x X-coordinate of the point.
 * @param y Y-coordinate of the point.
 * @param data Pointer to the t_data structure.
 * @return 1 if the wall is hit, 0 otherwise.
 */
int						wall_hit(float x, float y, t_data *data);

/**
 * @brief Function to get the horizontal intersection point of a wall.
 * @param data Pointer to the t_data structure.
 * @param angl Angle of the ray.
 * @return Horizontal intersection distance.
 */
float					find_x_collision(t_data *data, float angl);

/**
 * @brief Function to get the vertical intersection point of a wall.
 * @param data Pointer to the t_data structure.
 * @param angl Angle of the ray.
 * @return Vertical intersection distance.
 */
float					find_y_collision(t_data *data, float angl);

/**
 * @brief Function to cast rays for rendering walls in the game.
 * @param data Pointer to the t_data structure.
 */
void					cast_rays(t_data *data);

/**
 * @brief Game loop function to handle player movement, ray casting, and
 * rendering.
 * @param tmp Pointer to the t_data structure.
 */
void					game_hook(void *tmp);

/**
 * @brief Function to initialize the player structure.
 * @param data The t_data structure.
 */
void					init_player(t_data *data);

/**
 * @brief Function to start the Cub3D game.
 * @param map Pointer to the game data structure.
 */
void					start_the_game(t_map *map, char *map_argv);

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
	it adjusts the ray's
 * distance to correct for fisheye distortion.
 *
 * @param mlx The main data structure.
 */
void					update_ray(t_data *data);
int						load_textures(t_data *data);

#endif // CUB3D_H
