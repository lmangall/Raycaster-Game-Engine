#include "cub3d.h"

void	game_hook(void *tmp)
{
	t_data	*data;

	data = (t_data *)tmp;
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	apply_movement(data, 0, 0);
	raycasting(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	parser(argc, argv, &data);
	init_data(&data);
	mlx_loop_hook(data.mlx, &game_hook, &data);
	mlx_loop_hook(data.mlx, &key_hook, &data);
	mlx_loop(data.mlx);
	free_exit(&data);
	return (0);
}
