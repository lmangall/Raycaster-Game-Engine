// #include "../include/cub3d.h"
#include "cub3d.h"

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

int	main(int argc, char **argv)
{
	t_data	*data;

	// t_map *data = ft_calloc(1, sizeof(t_map));
	data = ft_calloc(1, sizeof(t_data));
	data = calloc(1, sizeof(t_map));
	// (void)argc;
	// (void)data;
	parser(argc, argv, data);
	// parse_map(argv[1], data);
	// start_the_game(data, argv[2]); // start the game
	// map = calloc(1, sizeof(t_map));
	// parse_map(argv[1], map);
	// init(map, argv[2]);
	load_textures(data);
	data->ray = calloc(1, sizeof(t_ray));
	data->player = calloc(1, sizeof(t_player));
	init_player(data);
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", 0);
	mlx_loop_hook(data->mlx, &game_loop, &data);
	mlx_key_hook(data->mlx, &mlx_key, &data);
	mlx_loop(data->mlx);
	free_exit(data);
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	// t_data *data = calloc(1, sizeof(t_map));
// 	t_data *data;

// 	(void)argc;
// 	// data = calloc(1, sizeof(t_data));
// 	data = malloc(sizeof(t_data));
// 	data->argv = argv[1];
// 	// implement checks.c for args

// 	init(data, argv[2]);
// 	mlx_loop_hook(data->mlx, &game_loop, data);
// 	mlx_key_hook(data->mlx, &mlx_key, data);
// 	mlx_loop(data->mlx);
// 	ft_exit(data);
// 	return (0);
// }