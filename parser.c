
#include"cub3d.h"


void	parse_map(char *argv, t_map *map )
{
	char	*map1d;
	char	**map2d;

	map1d = cub_to_str(argv);
	map2d = ft_split(map1d, '\n');
	map->map2d = map2d;
	map->h_map = 9;
	map->w_map = ft_strlen(map2d[0]);
	map->p_x = 14;
	map->p_y = 3;
// PrintMap(map);
	free(map1d);
}




// if (str[i] = 'N' && str[i+1] = 'O')
// 	{
// 		while(str[i] == ' ')
// 			i++;
// 		while(str* != ' ' && str* != '\n')
// 			j++;
// 		NO = malloc(sizeof(char) * j);
// 		ft_strlcpy(NO, str + i, j);

// 	}
	







// char *get_identifier_value(const char *str, const char *identifier) {
//     // Find the position of the identifier in the string
//     const char *pos = strstr(str, identifier);

//     // If the identifier is not found, return NULL
//     if (pos == NULL) {
//         return NULL;
//     }

//     // Move the pointer to the character after the identifier
//     pos += ft_strlen(identifier);

//     // Skip spaces
//     while (*pos == ' ') {
//         pos++;
//     }

//     // Find the length of the value
//     size_t value_length = 0;
//     while (pos[value_length] != ' ' && pos[value_length] != '\n' && pos[value_length] != '\0') {
//         value_length++;
//     }

//     // Allocate memory for the value and copy it
//     char *value = (char *)malloc(value_length + 1);
//     if (value == NULL) {
//         // Memory allocation failed
//         return NULL;
//     }

//     ft_strlcpy(value, pos, value_length);
//     value[value_length] = '\0';

//     return value;
// }

// Example usage:
// char *value = get_identifier_value("NO 123 456", "NO");
// printf("%s\n", value); // Output: 123
// free(value);





	

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