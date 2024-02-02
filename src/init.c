
#include "../include/cub3d.h"

 #define M_PI 3.14159265358979323846

void	init_player(t_data *data) // init the player structure
{
	data->player->x_pos_px = data->map->p_x * TILE_SIZE + TILE_SIZE / 2;
	// player x position in pixels in the center of the tile
	data->player->y_pos_px = data->map->p_y * TILE_SIZE + TILE_SIZE / 2;
	// player y position in pixels in the center of the tile
	data->player->fov_rd = (FOV * M_PI) / 180;
	// field of view in radians
	data->player->orientation_angle_rd = M_PI;
	data->player->lateral_move = L_NONE;
	data->player->rotation = R_NONE;
	data->player->longitudinal_move = NONE;

}