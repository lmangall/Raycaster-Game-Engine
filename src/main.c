#include "../include/cub3d.h"

void	game_loop(void *tmp) // game loop
{
	t_data *data;

	data = (t_data *)tmp;
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	hook(data, 0, 0);
	raycasting(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

void	init_the_player(t_data data) // init the player structure
{
	data.player->x_pos_px = data.map->p_x * TILE_SIZE + TILE_SIZE / 2;
	// player x position in pixels in the center of the tile
	data.player->y_pos_px = data.map->p_y * TILE_SIZE + TILE_SIZE / 2;
	// player y position in pixels in the center of the tile
	data.player->fov_rd = (FOV * M_PI) / 180;
	// field of view in radians
	data.player->orientation_angle_rd = M_PI;
	// player angle
	// the rest of the variables are initialized to zero by calloc
}

void	start_the_game(t_map *map, char *map_argv) // start the game
{
	t_data data;

	(void)map_argv;
	// load_textures(&data, map_argv);

	char *map_lines;
	map_lines = cub_to_str(map_argv);

	load_textures(&data, map_lines);

	data.map = map;
	// init the data structure
	data.player = calloc(1, sizeof(t_player));
	// init the player structure i'm using calloc to initialize the variables to zero
	data.ray = calloc(1, sizeof(t_ray));
	// init the ray structure
	data.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", 0);
	// init the data pointer
	init_the_player(data);
	// init the player structure
	mlx_loop_hook(data.mlx, &game_loop, &data); // game loop
	mlx_key_hook(data.mlx, &mlx_key, &data);
	// key press and release
	mlx_loop(data.mlx); // mlx loop
	free_exit(&data);
	// exit the game
}

int	main(int argc, char **argv)
{
	t_map *data = calloc(1, sizeof(t_map));

	(void)argc;

	// if (argc != 2)
	// {
	//   printf("Error\nWrong number of arguments\n");
	//   return (0);
	// }
	// atexit(v);
	parse_map(argv[1], data);

	start_the_game(data, argv[2]); // start the game
	return (0);
}