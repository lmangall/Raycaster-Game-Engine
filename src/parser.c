
#include "../include/cub3d.h"

// ADD IT TO LIBFT
/**
 * @file   my_strstr.c
 * @brief  Find the first occurrence of a substring in a string.
 *
 * This function searches for the first occurrence of the substring `to_find`
 * within the string `str`. If the substring is found, a pointer to the
 * beginning of the substring within the original string is returned. If the
 * substring is not found, a null pointer is returned.
 *
 * @param  str      The string to search within.
 * @param  to_find  The substring to search for.
 * @return          A pointer to the first occurrence of the substring in the
 *                  string, or a null pointer if the substring is not found.
 */
static char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
			{
				return (str + i);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	parse_map(char *argv, t_map *map)
{
	char	*map_str;
	char	**map2d;

	map_str = cub_to_str(argv);
	map2d = ft_split(map_str, '\n');
	map->grid = map2d;
	map->h_map = 9;
	map->w_map = ft_strlen(map2d[0]);
	map->p_x = 14;
	map->p_y = 3;
	free(map_str);
}

int	load_textures(t_data *data, char *map_str)
{
	t_textures	*textures;
	char		*value;

	printf("Loading textures...\n");
	printf("map_str: %s\n", map_str);
	textures = data->textures;
	value = get_identifier_value(map_str, "NO");
	textures->north = mlx_load_png(value);
	// free(value);
	value = get_identifier_value(map_str, "SO");
	textures->south = mlx_load_png(value);
	// free(value);
	value = get_identifier_value(map_str, "WE");
	textures->west = mlx_load_png(value);
	// free(value);
	value = get_identifier_value(map_str, "EA");
	textures->east = mlx_load_png(value);
	// free(value);
	// value = get_identifier_value(map_str, "F");
	// textures->ceiling = mlx_load_png(value);
	// free(value);
	// value = get_identifier_value(map_str, "C");
	// textures->floor = mlx_load_png(value);
	if (value != NULL)
		free(value);
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
	char *line;
	char *map_lines;
	int fd;

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