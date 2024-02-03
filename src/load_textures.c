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
	// init_t_texture(textures);
	north = remove_new_line_char_new(data->map->textures_paths->north);
	south = remove_new_line_char_new(data->map->textures_paths->south);
	west = remove_new_line_char_new(data->map->textures_paths->west);
	east = remove_new_line_char_new(data->map->textures_paths->east);
	// free(data->map->textures_paths->north);
	// free(data->map->textures_paths->south);
	// free(data->map->textures_paths->west);
	// free(data->map->textures_paths->east);
	textures->north = mlx_load_png(north);
	textures->south = mlx_load_png(south);
	textures->west = mlx_load_png(west);
	textures->east = mlx_load_png(east);
	data->textures = textures;

	return (0);
}