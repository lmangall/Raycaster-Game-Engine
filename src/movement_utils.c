
#include "../include/cub3d.h"

int	is_wall(t_data *data, double x, double y)
{
	int	map_grid_y;
	int	map_grid_x;

	map_grid_x = (x / TILE_SIZE);
	map_grid_y = (y / TILE_SIZE);
	if (data->map->grid[map_grid_y][map_grid_x] == '1'
		|| (data->map->grid[map_grid_y][data->player->x_pos_px
			/ TILE_SIZE] == '1' || data->map->grid[data->player->y_pos_px
			/ TILE_SIZE][map_grid_x] == '1'))
		return (1);
	return (0);
}
