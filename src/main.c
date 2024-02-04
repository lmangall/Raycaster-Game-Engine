#include "cub3d.h"

void	game_hook(void *tmp)
{
	t_data	*data;

	data = (t_data *)tmp;
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	raycasting(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
}

static void	print_textures(t_textures *textures)
{
	printf("north width: %u\n", textures->north->width);
	printf("north height: %u\n", textures->north->height);
	printf("south width: %u\n", textures->south->width);
	printf("south height: %u\n", textures->south->height);
	printf("west width: %u\n", textures->west->width);
	printf("west height: %u\n", textures->west->height);
	printf("east width: %u\n", textures->east->width);
	printf("east height: %u\n", textures->east->height);
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
		printf("\nMode PARSE ONLY ON!\n");
		free_exit_parser(&data);
	}
	load_textures(&data);
	print_textures(data.textures);
	init_data(&data);
	// to be placed somewhere else
	render_background(data.mlx, data.map->c, data.map->f);
	mlx_loop_hook(data.mlx, &key_hook, &data);
	mlx_loop_hook(data.mlx, &game_hook, &data);
	mlx_loop(data.mlx);
	free_exit(&data);
	return (0);
}
