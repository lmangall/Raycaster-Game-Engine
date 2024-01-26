#ifndef CUB3D_H
#define CUB3D_H

/**
 * @file cub3d.h
 * @brief Header file for the Cub3D game.
 */

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "lib/MLX42/include/MLX42/MLX42.h"
# include "lib/libft/src/libft.h"
#include <sys/stat.h>
#include <fcntl.h>


# define S_W 1900
# define S_H 1000
# define TILE_SIZE 30
# define FOV 60
# define ROTATION_SPEED 0.045
# define PLAYER_SPEED 4




/**
 * @brief Structure to save the path to textures.
 */
typedef struct s_textures {
    mlx_texture_t *no; /**< Path to the north texture. */
    mlx_texture_t *so; /**< Path to the south texture. */
    mlx_texture_t *we; /**< Path to the west texture. */
    mlx_texture_t *ea; /**< Path to the east texture. */
    mlx_texture_t *f; /**< Path to the floor texture. */
    mlx_texture_t *c; /**< Path to the ceiling texture. */
} t_textures;



/**
 * @brief Structure to represent the player in the game.
 */
typedef struct s_player {
    int plyr_x; /**< Player x position in pixels. */
    int plyr_y; /**< Player y position in pixels. */
    double angle; /**< Player angle. */
    float fov_rd; /**< Field of view in radians. */
    int rot; /**< Rotation flag. */
    int l_r; /**< Left-right flag. */
    int u_d; /**< Up-down flag. */
} t_player;

/**
 * @brief Structure to represent a ray in the game.
 */
typedef struct s_ray {
    double ray_ngl; /**< Ray angle. */
    double distance; /**< Distance to the wall. */
    int flag; /**< Flag for the wall. */
} t_ray;

/**
 * @brief Structure to represent game data, including the map.
 */
typedef struct s_map {
    char **map2d; /**< 2D array representing the map. */
    int p_x; /**< Player x position in the map. */
    int p_y; /**< Player y position in the map. */
    int w_map; /**< Map width. */
    int h_map; /**< Map height. */
} t_map;

/**
 * @brief Structure to hold MLX-related elements and game data.
 */
typedef struct s_mlx {
    mlx_image_t *img; /**< Pointer to the image. */
    mlx_t *mlx_p; /**< Pointer to the MLX instance. */
    t_ray *ray; /**< Pointer to the ray structure. */
    t_map *dt; /**< Pointer to the data structure. */
    t_player *ply; /**< Pointer to the player structure. */
    t_textures *textures; /**< Pointer to the textures structure. */
} t_mlx;





//PARSER:
void	parse_map(char *argv, t_map *map);
char	*cub_to_str(char *map);





//TEXTURES:
/**
 * @brief Get the value after a specified identifier in a string.
 *
 * This function extracts the part of the string that comes after the specified
 * identifier. The identifier can be NO, SO, WE, EA, F, or C.
 *
 * @param val The value to search for.
 * @param identifier The identifier to search for in the string.
 * @return A dynamically allocated string containing the value after the identifier.
 *         The caller is responsible for freeing the memory using free().
 *         If the identifier is not found or memory allocation fails, it returns NULL.
 */
char *get_identifier_value(char *val, char *identifier);

int	load_textures(t_mlx *mlx, char *map_str);




/**
 * @brief Function to handle cleanup and exit the game.
 * @param mlx Pointer to the t_mlx structure.
 */
void ft_exit(t_mlx *mlx);

/**
 * @brief Function to handle key release events.
 * @param keydata Key data for the pressed key.
 * @param mlx Pointer to the t_mlx structure.
 */
void ft_reles(mlx_key_data_t keydata, t_mlx *mlx);

/**
 * @brief Function to handle key press events.
 * @param keydata Key data for the pressed key.
 * @param ml Pointer to the t_mlx structure.
 */
void mlx_key(mlx_key_data_t keydata, void *ml);

/**
 * @brief Function to rotate the player based on key input.
 * @param mlx Pointer to the t_mlx structure.
 * @param i Integer indicating the direction of rotation (1 for right, 0 for left).
 */
void rotate_player(t_mlx *mlx, int i);

/**
 * @brief Function to move the player based on key input.
 * @param mlx Pointer to the t_mlx structure.
 * @param move_x Amount to move in the x-direction.
 * @param move_y Amount to move in the y-direction.
 */
void move_player(t_mlx *mlx, double move_x, double move_y);

/**
 * @brief Function to handle player movement and rotation based on key input.
 * @param mlx Pointer to the t_mlx structure.
 * @param move_x Amount to move in the x-direction.
 * @param move_y Amount to move in the y-direction.
 */
void hook(t_mlx *mlx, double move_x, double move_y);

/**
 * @brief Function to put a pixel on the screen.
 * @param mlx Pointer to the t_mlx structure.
 * @param x X-coordinate of the pixel.
 * @param y Y-coordinate of the pixel.
 * @param color Color of the pixel.
 */
void my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);

/**
 * @brief Function to normalize an angle to be within the range [0, 2 * PI).
 * @param angle Angle to be normalized.
 * @return Normalized angle.
 */
float nor_angle(float angle);

/**
 * @brief Function to draw the floor and ceiling of the game.
 * @param mlx Pointer to the t_mlx structure.
 * @param ray Ray representing the current column.
 * @param t_pix Top pixel of the wall.
 * @param b_pix Bottom pixel of the wall.
 */
void draw_floor_ceiling(t_mlx *mlx, int ray, int t_pix, int b_pix);

/**
 * @brief Function to get the color of the wall based on its orientation.
 * @param mlx Pointer to the t_mlx structure.
 * @param flag Flag indicating wall orientation (0 for vertical, 1 for horizontal).
 * @return Color of the wall.
 */
int get_color(t_mlx *mlx, int flag);

/**
 * @brief Function to draw a wall on the screen.
 * @param mlx Pointer to the t_mlx structure.
 * @param ray Ray representing the current column.
 * @param t_pix Top pixel of the wall.
 * @param b_pix Bottom pixel of the wall.
 */
void draw_wall(t_mlx *mlx, int ray, int t_pix, int b_pix);

/**
 * @brief Function to render a wall on the screen.
 * @param mlx Pointer to the t_mlx structure.
 * @param ray Ray representing the current column.
 */
void render_wall(t_mlx *mlx, int ray);

/**
 * @brief Function to cast rays and render the walls in the game.
 * @param mlx Pointer to the t_mlx structure.
 */
void cast_rays(t_mlx *mlx);

/**
 * @brief Function to check if a point lies in a specified quadrant of the unit circle.
 * @param angle Angle to check.
 * @param c Character indicating the axis ('x' or 'y').
 * @return 1 if the point lies in the specified quadrant, 0 otherwise.
 */
int unit_circle(float angle, char c);

/**
 * @brief Function to check and update intersection points for horizontal or vertical walls.
 * @param angle Angle of the ray.
 * @param inter Pointer to the intersection point, updated based on the direction.
 * @param step Pointer to the step size, adjusted based on the direction.
 * @param is_horizon Flag indicating whether the intersection is for a horizontal (1) or vertical (0) direction.
 * @return -1 if there is an intersection, 1 otherwise.
 */
int inter_check(float angle, float *inter, float *step, int is_horizon);

/**
 * @brief Function to check if a wall is hit based on coordinates.
 * @param x X-coordinate of the point.
 * @param y Y-coordinate of the point.
 * @param mlx Pointer to the t_mlx structure.
 * @return 1 if the wall is hit, 0 otherwise.
 */
int wall_hit(float x, float y, t_mlx *mlx);

/**
 * @brief Function to get the horizontal intersection point of a wall.
 * @param mlx Pointer to the t_mlx structure.
 * @param angl Angle of the ray.
 * @return Horizontal intersection distance.
 */
float get_h_inter(t_mlx *mlx, float angl);

/**
 * @brief Function to get the vertical intersection point of a wall.
 * @param mlx Pointer to the t_mlx structure.
 * @param angl Angle of the ray.
 * @return Vertical intersection distance.
 */
float get_v_inter(t_mlx *mlx, float angl);

/**
 * @brief Function to cast rays for rendering walls in the game.
 * @param mlx Pointer to the t_mlx structure.
 */
void cast_rays(t_mlx *mlx);

/**
 * @brief Game loop function to handle player movement, ray casting, and rendering.
 * @param ml Pointer to the t_mlx structure.
 */
void game_loop(void *ml);

/**
 * @brief Function to initialize the player structure.
 * @param mlx The t_mlx structure.
 */
void init_the_player(t_mlx mlx);

/**
 * @brief Function to start the Cub3D game.
 * @param dt Pointer to the game data structure.
 */
void start_the_game(t_map *dt, char *map_argv);

/**
 * @brief Function to initialize the game data structure with a predefined map.
 * @return Pointer to the initialized game data structure.
 */
t_map *init_argumet();

/**
 * @brief Main function to initialize the game and start the main loop.
 * @return 0 if the program runs successfully.
 */
int main();

#endif // CUB3D_H
