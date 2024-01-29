#include "cub3d.h"

typedef enum
{
	NOT_FOUND,
	FOUND
}				e_status;

typedef struct s_map_elements
{
	e_status	no;
	e_status	so;
	e_status	we;
	e_status	ea;
	e_status	c;
	e_status	f;
}				t_map_elements;

int	process_map_elements(char *line, const char *identifier,
		e_status *element_status)
{
	if (ft_strncmp(line, identifier, ft_strlen(identifier)) == 0)
	{
		if (*element_status == FOUND)
		{
			printf("Error\n");
			printf("Duplicate %s identifier\n", identifier);
			// free whatever was allocated before
			exit(EXIT_FAILURE);
		}
		else
		{
			*element_status = FOUND;
			return (SUCCESS);
		}
	}
	else
		return (FAILURE);
}

void	collect_elements_data_path(char *line, char *identifier, char *target)
{
	char	*start;
	char	*end;

	// Skip spaces
	while (*line == ' ')
		line++;
	// Skip identifier
	// Between identifier and data there can be spaces
	// but it's not mandatory
	line += ft_strlen(identifier);
	// Skip spaces
	while (*line == ' ')
		line++;
	// Get data
	start = line;
	while (*line != ' ')
		line++;
	end = line;
	target = ft_substr(start, 0, end - start);
	// Skip spaces
	while (*line == ' ')
		line++;
	// Check for extra data
	if (*line != '\0')
	{
		printf("Error\n");
		printf("Extra data after %s identifier\n", identifier);
		free(target);
		// free whatever was allocated before
		exit(EXIT_FAILURE);
	}
}

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

int	str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

void	collect_elements_data_rgba(char *line, char *identifier, t_data *data)
{
	char	*start;
	char	*end;
	char	*rgb_str;
	char	**rgb_values;
	int		rgb[3];
	int		i;
	t_rgba	*target;

	target = NULL;
	if (ft_strncmp(identifier, "C", ft_strlen(identifier)) == 0)
		target = &data->map->c;
	else if (ft_strncmp(identifier, "F", ft_strlen(identifier)) == 0)
		target = &data->map->f;
	// Skip spaces
	while (*line == ' ')
		line++;
	// Skip identifier
	line += ft_strlen(identifier);
	// Skip spaces
	while (*line == ' ')
		line++;
	// Extract RGB string
	start = line;
	while (*line != ' ' && *line != '\0')
		line++;
	end = line;
	rgb_str = ft_substr(start, 0, end - start);
	// Split RGB string
	rgb_values = ft_split(rgb_str, ',');
	free(rgb_str);
	// Check length of RGB array
	i = 0;
	while (rgb_values[i] != NULL)
		i++;
	if (i != 3)
	{
		printf("Error\n");
		printf("Invalid RGB values\n");
		free_str_arr(rgb_values);
		// free whatever was allocated before
		exit(EXIT_FAILURE);
	}
	// Check for not int values
	i = 0;
	while (rgb_values[i] != NULL)
	{
		if (!str_isdigit(rgb_values[i]))
		{
			printf("Error\n");
			printf("Invalid RGB values\n");
			free_str_arr(rgb_values);
			// free whatever was allocated before
			exit(EXIT_FAILURE);
		}
		i++;
	}
	// Convert and validate RGB values
	i = 0;
	while (rgb_values[i] != NULL)
	{
		rgb[i] = ft_atoi(rgb_values[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			printf("Error\n");
			printf("Invalid RGB values\n");
			free_str_arr(rgb_values);
			// free whatever was allocated before
			exit(EXIT_FAILURE);
		}
		i++;
	}
	// Skip spaces
	line++;
	while (*line == ' ')
		line++;
	// Check for extra data
	if (*line != '\0')
	{
		printf("Error\n");
		printf("Extra data after %s identifier\n", identifier);
		free_str_arr(rgb_values);
		// free whatever was allocated before
		exit(EXIT_FAILURE);
	}
	// Assign RGB values to target
	target->r = rgb[0];
	target->g = rgb[1];
	target->b = rgb[2];
	free_str_arr(rgb_values);
}

void	collect_elements_data(char *line, char *identifier, t_data *data)
{
	if (ft_strncmp(identifier, "NO", ft_strlen(identifier)) == 0)
		collect_elements_data_path(line, identifier,
			data->textures_paths->north);
	else if (ft_strncmp(identifier, "SO", ft_strlen(identifier)) == 0)
		collect_elements_data_path(line, identifier,
			data->textures_paths->south);
	else if (ft_strncmp(identifier, "WE", ft_strlen(identifier)) == 0)
		collect_elements_data_path(line, identifier,
			data->textures_paths->west);
	else if (ft_strncmp(identifier, "EA", ft_strlen(identifier)) == 0)
		collect_elements_data_path(line, identifier,
			data->textures_paths->east);
	else if (ft_strncmp(identifier, "C", ft_strlen(identifier)) == 0)
		collect_elements_data_rgba(line, identifier, data);
	else if (ft_strncmp(identifier, "F", ft_strlen(identifier)) == 0)
		collect_elements_data_rgba(line, identifier, data);
	else
	{
		printf("Error\n");
		printf("Invalid identifier\n");
		// free whatever was allocated before
		exit(EXIT_FAILURE);
	}
}

void	process_map(char **lines_arr, t_data *data)
{
	t_map_elements	elements;
	char			*line;
	int				i;

	elements.no = NOT_FOUND;
	elements.so = NOT_FOUND;
	elements.we = NOT_FOUND;
	elements.ea = NOT_FOUND;
	elements.c = NOT_FOUND;
	elements.f = NOT_FOUND;
	i = 0;
	while (lines_arr[i] != NULL)
	{
		line = lines_arr[i];
		// Skip empty lines
		if (line[0] == '\0')
		{
			i++;
			continue ;
		}
		// Skip initial spaces
		while (*line == ' ')
			line++;
		// Process map elements
		if (process_map_elements(line, "NO", &elements.no))
			collect_elements_data(line, "NO", data);
		else if (process_map_elements(line, "SO", &elements.so))
			collect_elements_data(line, "SO", data);
		else if (process_map_elements(line, "WE", &elements.we))
			collect_elements_data(line, "WE", data);
		else if (process_map_elements(line, "EA", &elements.ea))
			collect_elements_data(line, "EA", data);
		else if (process_map_elements(line, "C", &elements.c))
			collect_elements_data(line, "C", data);
		else if (process_map_elements(line, "F", &elements.f))
			collect_elements_data(line, "F", data);
		else
		{
			printf("Error\n");
			printf("Invalid identifier\n");
			// free whatever was allocated before
			exit(EXIT_FAILURE);
		}
		// Break if all elements were found
		if (elements.no == FOUND && elements.so == FOUND && elements.we == FOUND
			&& elements.ea == FOUND && elements.c == FOUND
			&& elements.f == FOUND)
			break ;
		i++;
	}
	// Then process map
	printf("Processing map content...\n");
}

void	print_lines_arr(char **lines_arr)
{
	int	i;

	printf("Printing lines_arr...\n");
	if (lines_arr == NULL)
	{
		printf("No lines to print.\n");
		return ;
	}
	i = 0;
	while (lines_arr[i] != NULL)
	{
		printf("%s\n", lines_arr[i]);
		i++;
	}
}

char	**parse_file(char *file_path)
{
	int		fd;
	char	*line;
	char	**lines_arr;
	size_t	lines_nbr;
	size_t	capacity;
	char	**tmp;
	size_t	i;

	printf("Parsing file...\n");
	lines_nbr = 0;
	capacity = 10;
	i = 0;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (NULL);
	}
	lines_arr = malloc(capacity * sizeof(char *));
	if (!lines_arr)
	{
		close(fd);
		return (NULL);
	}
	while ((line = get_next_line(fd)))
	{
		// printf("line: %s\n", line);
		if (lines_nbr == capacity)
		{
			// printf("Reallocating...\n");
			// printf("capacity: %zu\n", capacity);
			// printf("lines_nbr: %zu\n", lines_nbr);
			capacity *= 2;
			tmp = ft_easy_realloc(lines_arr, (capacity / 2) * sizeof(char *),
				capacity * sizeof(char *));
			if (!tmp)
			{
				while (i < lines_nbr)
				{
					free(lines_arr[i]);
					i++;
				}
				free(lines_arr);
				close(fd);
				// We can exit here.
				return (NULL);
			}
			lines_arr = tmp;
		}
		lines_arr[lines_nbr++] = line;
		// printf("lines_nbr: %zu\n", lines_nbr);
		// printf("lines_arr[%zu]: %s\n", lines_nbr - 1, lines_arr[lines_nbr
		// - 1]);
	}
	close(fd);
	// printf("capacity: %zu\n", capacity);
	// printf("lines_nbr: %zu\n", lines_nbr);
	tmp = ft_easy_realloc(lines_arr, capacity * sizeof(char *), (lines_nbr + 1)
		* sizeof(char *));
	if (!tmp)
	{
		for (size_t i = 0; i < lines_nbr; i++)
			free(lines_arr[i]);
		free(lines_arr);
		return (NULL);
	}
	lines_arr = tmp;
	lines_arr[lines_nbr] = NULL;
	// printf("lines_nbr: %zu\n", lines_nbr);
	// printf("last line before NULL: lines_arr[%zu]: %s\n", lines_nbr,
	// 	lines_arr[lines_nbr - 1]);
	// printf("Printing lines_arr before exiting...\n");
	// i = 0;
	// printf("printing pointers...\n");
	// while (lines_arr[i] != NULL)
	// {
	// 	printf("%p\n", lines_arr[i]);
	// 	i++;
	// }
	// i = 0;
	// while (lines_arr[i] != NULL)
	// {
	// 	if (lines_arr[i][0] == '\0')
	// 		printf("Empty line\n");
	// 	else
	// 		printf("%s\n", lines_arr[i]);
	// 	i++;
	// }
	// printf("Exiting parse_file...\n");
	return (lines_arr);
}
