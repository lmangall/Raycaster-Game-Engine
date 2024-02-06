#include "cub3d.h"

void	init_t_texture(t_textures *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	textures->ceiling = NULL;
	textures->floor = NULL;
}

int	load_textures(t_data *data)
{
	t_textures *textures;

	textures = ft_calloc(1, sizeof(t_textures));
	textures->north = mlx_load_png(data->map->textures_paths->north);
	textures->south = mlx_load_png(data->map->textures_paths->south);
	textures->west = mlx_load_png(data->map->textures_paths->west);
	textures->east = mlx_load_png(data->map->textures_paths->east);
	data->textures = textures;

	return (0);
}