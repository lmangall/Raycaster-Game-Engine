/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:26:37 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/07 21:43:31 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "MLX42.h"
# include "libft.h"
# include "structs.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>

// For clarity in the code
# define SUCCESS 0
# define FAILURE 1
// A window to our world
# define WINDOW_WIDTH 1900
# define WINDOW_HEIGHT 1000
// Our world
# define TILE_SIZE 30
# define FOV 60
# define PLAYER_ROTATION_SPEED 0.045
# define PLAYER_TRANSLATION_SPEED 4
# define ERROR_OPENING_FILE "File not found or corrupted."
// Ray directions
# define RIGHT 10
# define LEFT 9
# define UP 8
# define DOWN 7

// Parser enums for clear code:
typedef enum e_mode
{
	PARSE_ONLY,
	FULL_EXPERIENCE
}						t_mode;

typedef enum e_debug
{
	OFF,
	ALL,
	ONLY_FINAL
}						t_debug;

typedef enum e_status
{
	NOT_FOUND,
	FOUND
}						t_status;

typedef struct s_rgba
{
	int					r;
	int					g;
	int					b;
	int					a;
}						t_rgba;

typedef struct s_textures_paths
{
	char				*north;
	char				*south;
	char				*west;
	char				*east;
}						t_textures_paths;

typedef struct s_textures
{
	mlx_texture_t		*north;
	mlx_texture_t		*south;
	mlx_texture_t		*west;
	mlx_texture_t		*east;
	mlx_texture_t		*floor;
	mlx_texture_t		*ceiling;
}						t_textures;

typedef struct s_map_elements
{
	t_status			no;
	t_status			so;
	t_status			we;
	t_status			ea;
	t_status			c;
	t_status			f;
}						t_map_elements;

typedef struct s_map
{
	char				**lines_arr;
	char				**grid;
	int					p_x;
	int					p_y;
	char				player_orientation;
	t_status			player_found;
	int					width;
	int					height;
	t_rgba				c;
	t_rgba				f;
	t_textures_paths	*textures_paths;
	t_map_elements		elements;

}						t_map;

typedef enum e_rotation
{
	R_NONE = 0,
	R_RIGHT = 1,
	R_LEFT = 2
}						t_rotation;

typedef enum t_lateral_move
{
	L_NONE = 0,
	L_RIGHT = 1,
	L_LEFT = 2
}						t_lateral_move;

typedef enum t_longitudinal_move
{
	NONE = 0,
	FORWARD = 1,
	BACKWARD = 2
}						t_longitudinal_move;

typedef struct s_player
{
	int					x_pos_px;
	int					y_pos_px;
	double				orientation_angle_rd;
	float				fov_rd;
	int					rotation_speed;
	int					translation_speed;
	t_rotation			rotation;
	t_lateral_move		lateral_move;
	t_longitudinal_move	longitudinal_move;
}						t_player;

typedef enum e_wall_collision
{
	NO_COLLISION = 0,
	HORIZONTAL = 1,
	VERTICAL = 2
}						t_wall_collision;

typedef struct s_ray
{
	double				angle_rd;
	double				length;
	t_wall_collision	wall_collision_orientation;
	double				horizontal_x;
	double				horizontal_y;
	double				vertical_x;
	double				vertical_y;
	int					wall_orientation;
	int					screen_x;
	mlx_texture_t		*current_texture;
	int					wall_h;
	int					higher_pixel;
	int					lower_pixel;
}						t_ray;

// The "main" struct
typedef struct s_data
{
	mlx_image_t			*img;
	mlx_image_t			*minimap;
	mlx_image_t			*background;
	mlx_t				*mlx;
	t_ray				*ray;
	t_map				*map;
	t_player			*player;
	t_textures			*textures;
	t_debug				debug;
}						t_data;

#endif