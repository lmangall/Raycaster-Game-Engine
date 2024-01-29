
#include "../include/cub3d.h"

void	init_player(t_data *data) // init the player structure
{
	data->player->x_pos_px = data->map->p_x * TILE_SIZE + TILE_SIZE / 2;
	// player x position in pixels in the center of the tile
	data->player->y_pos_px = data->map->p_y * TILE_SIZE + TILE_SIZE / 2;
	// player y position in pixels in the center of the tile
	data->player->fov_rd = (FOV * M_PI) / 180;
	// field of view in radians
	data->player->orientation_angle_rd = M_PI;
	// player angle
	// the rest of the variables are initialized to zero by calloc
}

void	init(t_map *map, char *map_argv)
{
	char	*map_lines;
	t_data	data;

	// data = calloc(1, sizeof(t_data));
	map_lines = cub_to_str(map_argv);
	load_textures(&data, map_lines);
	data.map = map;
	data.ray = calloc(1, sizeof(t_ray));
	data.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", 0);
	data.player = calloc(1, sizeof(t_player));
	init_player(&data);
	mlx_loop_hook(data.mlx, &game_loop, &data);
	mlx_key_hook(data.mlx, &mlx_key, &data);
	mlx_loop(data.mlx);
	ft_exit(&data);
}

// void	init(t_data *data, char *map_argv)
// {
// 	t_map	*map;
// 	char	*map_lines;

// 	map = calloc(1, sizeof(t_map));
// 	parse_map(data->argv, map);
// 	map_lines = cub_to_str(map_argv);
// 	load_textures(data, map_lines);
// 	data->map = map;
// 	data->ray = calloc(1, sizeof(t_ray));
// 	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", 0);
// 	data->player = calloc(1, sizeof(t_player));
// 	init_player(data);
// }
