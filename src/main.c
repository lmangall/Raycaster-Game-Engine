// #include "../include/cub3d.h"
#include "cub3d.h"


// static void move_player_forward_slowly(t_data *data) 
// {
//     double move_x = cos(data->player->orientation_angle_rd) * (PLAYER_TRANSLATION_SPEED / 2);
//     double move_y = sin(data->player->orientation_angle_rd) * (PLAYER_TRANSLATION_SPEED / 2);
// //    (void)data;
//     move_player(data, move_x, move_y);
// }

// static void print_player_data(t_data *data)
// {
// 	printf("\033[1;32mPlayer data:\n\033[0m");
// 	printf("\033[1;32mPlayer x position: %d\n\033[0m", data->player->x_pos_px);
// 	printf("\033[1;32mPlayer y position: %d\n\033[0m", data->player->y_pos_px);
// 	printf("\033[1;32mPlayer orientation angle: %f\n\033[0m", data->player->orientation_angle_rd);
// 	printf("\033[1;32mPlayer rotation: %d\n\033[0m", data->player->rotation);
// 	printf("\033[1;32mPlayer lateral move: %d\n\033[0m", data->player->lateral_move);
// 	printf("\033[1;32mPlayer longitudinal move: %d\n\033[0m", data->player->longitudinal_move);
// }

void	game_loop(void *tmp) // game loop
{
	t_data *data;

	data = (t_data *)tmp;
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	//                 ARTIFICIAL MOVEMENT
	// move_player_forward_slowly(data);
	// rotate_player(data, 2);
	//				 END
	// print_player_data(data);//               debugging
	// movement_hook(data, 0, 0);
	hook(data, 0, 0);
	raycasting(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

void	init_data(t_data *data)
{
	load_textures(data);
	data->ray = calloc(1, sizeof(t_ray));
	// data->map = calloc(1, sizeof(t_map));
	data->player = calloc(1, sizeof(t_player));
	init_player(data);
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", 0);
}


int	main(int argc, char **argv)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	parser(argc, argv, data);
	init_data(data);
	// mlx_key_hook(data->mlx, &key_hook, &data);
	mlx_loop_hook(data->mlx, game_loop, data);
	mlx_key_hook(data->mlx, &mlx_key, &data);
	// mlx_loop_hook(data->mlx, key_hook, &data);
	mlx_loop(data->mlx);
	free_exit(data);
	return (0);
}
