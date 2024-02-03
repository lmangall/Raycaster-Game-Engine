
#include "../include/cub3d.h"

void	init_data(t_data *data)
{
	load_textures(data);
	data->ray = calloc(1, sizeof(t_ray));
	data->player = calloc(1, sizeof(t_player));
	init_player(data);
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", 0);
}

void	init_player(t_data *data)
{
	data->player->x_pos_px = data->map->p_x * TILE_SIZE + TILE_SIZE / 2;
	// player x position in pixels in the center of the tile
	data->player->y_pos_px = data->map->p_y * TILE_SIZE + TILE_SIZE / 2;
	// player y position in pixels in the center of the tile
	data->player->fov_rd = (FOV * M_PI) / 180;
	// field of view in radians
	data->player->orientation_angle_rd = M_PI;
	data->player->lateral_move = 0;
	data->player->rotation = 0;
	data->player->longitudinal_move = 0;
}