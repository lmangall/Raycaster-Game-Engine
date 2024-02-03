#include "cub3d.h"

void	game_loop(void *tmp)
{
	t_data	*data;

	data = (t_data *)tmp;
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	hook(data, 0, 0);
	raycasting(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_data *data;

	data = ft_calloc(1, sizeof(t_data));
	parser(argc, argv, data);
	free_exit_parser(data);
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