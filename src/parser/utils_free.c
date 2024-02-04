#include "cub3d.h"

void	free_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i] != NULL)
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

void	error_exit(char *error_message)
{
	printf("Error\n");
	printf("%s\n", error_message);
	exit(EXIT_FAILURE);
}

void	free_texture_paths(t_textures_paths *textures_paths)
{
	if (textures_paths == NULL)
		return ;
	if (textures_paths->north != NULL)
	{
		free(textures_paths->north);
		textures_paths->north = NULL;
	}
	if (textures_paths->south != NULL)
	{
		free(textures_paths->south);
		textures_paths->south = NULL;
	}
	if (textures_paths->west != NULL)
	{
		free(textures_paths->west);
		textures_paths->west = NULL;
	}
	if (textures_paths->east != NULL)
	{
		free(textures_paths->east);
		textures_paths->east = NULL;
	}
	free(textures_paths);
}

void	free_exit_parser(t_data *data, char *error_message)
{
	int	i;

	if (data->map->lines_arr != NULL)
		free_str_arr(data->map->lines_arr);
	if (data->map->grid != NULL)
	{
		i = 0;
		while (data->map->grid[i] && data->map->height > 0)
		{
			free(data->map->grid[i]);
			data->map->grid[i] = NULL;
			i++;
		}
		free(data->map->grid);
		data->map->grid = NULL;
	}
	free_texture_paths(data->map->textures_paths);
	if (data->map)
	{
		free(data->map);
		data->map = NULL;
	}
	free(data);
	data = NULL;
	error_exit(error_message);
}
