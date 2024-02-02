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

void	free_exit_parser(t_data *data)
{
	int	i;

	// free t_map struct
	// free char **grid
	if (data->map->grid != NULL)
	{
		i = 0;
		while (data->map->grid[i] && data->map->height > 0)
		{
			printf("data->map->grid[%d]'s ptr: %p\n", i, &data->map->grid[i]);
			printf("data->map->grid[%d]: %s\n", i, data->map->grid[i]);
			free(data->map->grid[i]);
			data->map->grid[i] = NULL;
			i++;
		}
		free(data->map->grid);
		data->map->grid = NULL;
	}
	/* int p_x, int p_y, char player_orientation, e_status player_found,
		int width, int height, t_rgba c and t_rgba f don't need to be freed.
		free the char
			* of the members of t_textures_paths and then texture_paths itself  */
	free(data->map->textures_paths->north);
	free(data->map->textures_paths->south);
	free(data->map->textures_paths->west);
	free(data->map->textures_paths->east);
	free(data->map->textures_paths);
	// free map
	free(data->map);
	data->map = NULL;
	free(data);
	data = NULL;
}

int	main(int argc, char **argv)
{
	t_data	*data;

	// t_map *data = ft_calloc(1, sizeof(t_map));
	data = ft_calloc(1, sizeof(t_data));
	// data = calloc(1, sizeof(t_map));
	// (void)argc;
	// (void)data;
	parser(argc, argv, data);
	printf("data->map->textures_paths.north: %s\n",
		data->map->textures_paths->north);
	printf("Exiting...\n");
	// free_exit_parser(data);
	// parse_map(argv[1], data);
	// start_the_game(data, argv[2]); // start the game
	// map = calloc(1, sizeof(t_map));
	// parse_map(argv[1], map);
	// init(map, argv[2]);
	load_textures(data);
	printf("mark -1\n");
	data->ray = calloc(1, sizeof(t_ray));
	data->player = calloc(1, sizeof(t_player));
	init_player(data);
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", 0);
	printf("mark\n");
	int mlx_loop_return = mlx_loop_hook(data->mlx, &game_loop, data);
	printf("mlx_loop_return (boolean): %d\n", mlx_loop_return);
	printf("mark 0\n");
	mlx_key_hook(data->mlx, &mlx_key, &data);
	// mlx_loop(data->mlx);
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