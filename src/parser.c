
#include "cub3d.h"

void	parse_map(char *argv, t_map *map)
{
	char	*map_str;
	char	**map2d;

	map_str = cub_to_str(argv);
	map2d = ft_split(map_str, '\n');
	map->grid = map2d;
	map->height = 9;
	map->width = ft_strlen(map2d[0]);
	map->p_x = 14;
	map->p_y = 3;
	free(map_str);
}

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
	t_textures	*textures;
	char		*north;
	char		*south;
	char		*west;
	char		*east;

	textures = ft_calloc(1, sizeof(t_textures));
	// Print all textures paths
	printf("Loading textures...\n");
	north = remove_new_line_char_new(data->map->textures_paths.north);
	south = remove_new_line_char_new(data->map->textures_paths.south);
	west = remove_new_line_char_new(data->map->textures_paths.west);
	east = remove_new_line_char_new(data->map->textures_paths.east);
	printf("north: %s\n", north);
	// textures = data->textures;
	// value = get_identifier_value(map_str, "NO");
	textures->north = mlx_load_png(north);
	printf("textures->north: %p\n", textures->north);
	// textures->north = mlx_load_png(data->map->textures_paths.north);
	// free(value);
	// value = get_identifier_value(map_str, "SO");
	textures->south = mlx_load_png(south);
	// textures->south = mlx_load_png(data->map->textures_paths.south);
	// free(value);
	// value = get_identifier_value(map_str, "WE");
	textures->west = mlx_load_png(west);
	// textures->west = mlx_load_png(data->map->textures_paths.west);
	// free(value);
	// value = get_identifier_value(map_str, "EA");
	textures->east = mlx_load_png(east);
	// textures->east = mlx_load_png(data->map->textures_paths.east);
	// free(value);
	// value = get_identifier_value(map_str, "F");
	// textures->ceiling = mlx_load_png(value);
	// free(value);
	// value = get_identifier_value(map_str, "C");
	// textures->floor = mlx_load_png(value);
	data->textures = textures;
	printf("Textures loaded.\n");
	return (0);
}

char	*get_identifier_value(char *map_str, char *identifier)
{
	char	*pos;
	size_t	value_length;
	char	*value;

	pos = ft_strstr(map_str, identifier);
	if (pos == NULL)
		return (NULL);
	pos += ft_strlen(identifier);
	while (*pos == ' ')
		pos++;
	value_length = 0;
	while (pos[value_length] != ' ' && pos[value_length] != '\n'
		&& pos[value_length] != '\0')
		value_length++;
	value = (char *)malloc(value_length + 1);
	if (value == NULL)
		return (NULL);
	ft_strlcpy(value, pos, value_length + 1);
	value[value_length] = '\0';
	return (value);
}

char	*cub_to_str(char *map)
{
	char	*line;
	char	*map_lines;
	int		fd;

	fd = open(map, O_RDONLY);
	map_lines = ft_calloc(1, 1);
	while (1)
	{
		line = get_next_line(fd);
		if (line)
		{
			map_lines = ft_strjoin(map_lines, line);
			free(line);
		}
		else
			break ;
	}
	close(fd);
	return (map_lines);
}
