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

int	main(int argc, char **argv)
{
	// t_data *data = calloc(1, sizeof(t_map));
	t_map *map;
	(void)argc;

	map = calloc(1, sizeof(t_map));
	// implement checks.c for args
	parse_map(argv[1], map);
	init(map, argv[2]);
	// mlx_loop_hook(data->mlx, &game_loop, &data);
	// mlx_key_hook(data->mlx, &mlx_key, &data);
	// mlx_loop(data->mlx);
	// ft_exit(data);
	return (0);
}