#include "cub3d.h"

void	free_exit_parser(t_data *data)
{
	int	i;

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
	free(data->map->textures_paths->south);
	free(data->map->textures_paths->west);
	free(data->map->textures_paths->east);
	free(data->map->textures_paths);
	free(data->map);
	data->map = NULL;
	free(data);
	data = NULL;
	printf("Exiting...\n");
	exit(0);
}

void	error_exit(char *error_message, t_data *data)
{
	(void)data;
	printf("Error\n");
	printf("%s\n", error_message);
	// free whatever was allocated before
	exit(EXIT_FAILURE);
}
