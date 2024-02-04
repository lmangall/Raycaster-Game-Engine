#include "cub3d.h"

static void	init_ray(t_data *data)
{
	// data->ray->angle = data->player->orientation_angle_rd
	// 	- (data->player->fov_rd / 2);

	if (data->map->player_orientation == 'N')
		data->player->orientation_angle_rd = 3 * M_PI_2;
	else if (data->map->player_orientation == 'S')
		data->player->orientation_angle_rd = M_PI_2;
	else if (data->map->player_orientation == 'E')
		data->player->orientation_angle_rd = 0;
	else if (data->map->player_orientation == 'W')
		data->player->orientation_angle_rd = M_PI;
}

void	game_hook(void *tmp)
{
	t_data	*data;

	data = (t_data *)tmp;
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	apply_movement(data, 0, 0);
	init_ray(data);
	raycasting(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_mode	mode;

	mode = FULL_EXPERIENCE;
	// mode = PARSE_ONLY;
	parser(argc, argv, &data);
	if (mode == PARSE_ONLY)
	{
		printf("Mode PARSE ONLY ON!\n");
		free_exit_parser(&data);
	}
	load_textures(&data);
	init_data(&data);
	// to be placed somewhere else
	render_background(data.mlx, data.map->c, data.map->f);
	mlx_loop_hook(data.mlx, &game_hook, &data);
	mlx_loop_hook(data.mlx, &key_hook, &data);
	mlx_loop(data.mlx);
	free_exit(&data);
	return (0);
}
