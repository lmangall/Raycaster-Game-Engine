#include "cub3d.h"

char	*remove_new_line_char_new(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\n')
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	return (new_str);
}

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
	char *north;
	char *south;
	char *west;
	char *east;

	textures = ft_calloc(1, sizeof(t_textures));
	// Print all textures paths
	printf("Loading textures...\n");
	printf("data->map->textures_paths.north: %s\n",
		data->map->textures_paths->north);
	printf("data->map->textures_paths.south: %s\n",
		data->map->textures_paths->south);
	printf("data->map->textures_paths.west: %s\n",
		data->map->textures_paths->west);
	printf("data->map->textures_paths.east: %s\n",
		data->map->textures_paths->east);
	north = remove_new_line_char_new(data->map->textures_paths->north);
	south = remove_new_line_char_new(data->map->textures_paths->south);
	west = remove_new_line_char_new(data->map->textures_paths->west);
	east = remove_new_line_char_new(data->map->textures_paths->east);
	printf("north: %s\n", north);
	textures->north = mlx_load_png(north);
	printf("textures->north: %p\n", textures->north);
	textures->south = mlx_load_png(south);
	textures->west = mlx_load_png(west);
	textures->east = mlx_load_png(east);
	data->textures = textures;
	printf("Textures loaded.\n");
	return (0);
}