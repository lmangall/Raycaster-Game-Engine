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

void	error_exit(char *error_message, t_data *data)
{
	(void)data;
	printf("Error\n");
	printf("%s\n", error_message);
	// free whatever was allocated before
	exit(EXIT_FAILURE);
}

int	check_identifier(char *line, const char *identifier,
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

	printf("collect_elements_data_path START\n");
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
	printf("line: %s\n", line);
	while (*line != ' ' && *line != '\0')
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
	printf("collect_elements_data_path END\n");
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

void	init_elements_status(t_map_elements *elements)
{
	elements->no = NOT_FOUND;
	elements->so = NOT_FOUND;
	elements->we = NOT_FOUND;
	elements->ea = NOT_FOUND;
	elements->c = NOT_FOUND;
	elements->f = NOT_FOUND;
}

void	process_map_elements(char *line, int *i, t_data *data,
		t_map_elements *elements)
{
	printf("process_map_elements START\n");
	// Skip empty lines
	if (line[0] == '\0')
	{
		printf("Empty line skipped in process_map_elements\n");
		return ;
	}
	// Skip initial spaces
	while (*line == ' ')
		line++;
	// Process map elements
	if (check_identifier(line, "NO", &elements->no))
		collect_elements_data(line, "NO", data);
	else if (check_identifier(line, "SO", &elements->so))
		collect_elements_data(line, "SO", data);
	else if (check_identifier(line, "WE", &elements->we))
		collect_elements_data(line, "WE", data);
	else if (check_identifier(line, "EA", &elements->ea))
		collect_elements_data(line, "EA", data);
	else if (check_identifier(line, "C", &elements->c))
		collect_elements_data(line, "C", data);
	else if (check_identifier(line, "F", &elements->f))
		collect_elements_data(line, "F", data);
	else
		error_exit("Invalid identifier", data);
	(*i)++;
	printf("process_map_elements END\n");
}

int	check_all_elements_found(t_map_elements *elements)
{
	printf("Checking if all elements have been found...\n");
	if (elements->no == FOUND && elements->so == FOUND && elements->we == FOUND
		&& elements->ea == FOUND && elements->c == FOUND
		&& elements->f == FOUND)
	{
		printf("All elements found\n");
		return (SUCCESS);
	}
	else
	{
		printf("Not all elements found\n");
		return (FAILURE);
	}
}

int	has_only_valid_chars(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'W' && line[i] != 'E')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

int	calculate_height(char **lines_arr, int first_line)
{
	int	i;
	int	height;

	i = first_line;
	height = 0;
	while (lines_arr[i] != NULL)
	{
		if (lines_arr[i][0] != '\0')
			height++;
		i++;
	}
	return (height);
}

int	find_max_width(char **lines_arr, int current_max_width)
{
	int	i;
	int	current_width;

	i = 0;
	while (lines_arr[i] != NULL)
	{
		current_width = ft_strlen(lines_arr[i]);
		if (current_width > current_max_width)
			current_max_width = current_width;
		i++;
	}
	return (current_max_width);
}

int	is_surrounded_by_walls(char **lines_arr, int current_line, int first_line,
		int last_line)
{
	int	i;

	if (current_line == first_line || current_line == last_line)
	{
		i = 0;
		while (lines_arr[current_line][i] != '\0')
		{
			if (lines_arr[current_line][i] != '1'
				&& lines_arr[current_line][i] != ' ')
				return (FAILURE);
			i++;
		}
	}
	else
	{
		// check fist and last char
		// skip spaces
		i = 0;
		while (lines_arr[current_line][i] == ' ')
			i++;
		if (lines_arr[current_line][i] != '1')
			return (FAILURE);
		i = ft_strlen(lines_arr[current_line]) - 1;
		while (lines_arr[current_line][i] == ' ')
			i--;
		if (lines_arr[current_line][i] != '1')
			return (FAILURE);
	}
	return (SUCCESS);
}

int	is_valid_space_sorrounding_char(char c)
{
	if (c == ' ' || c == '1')
		return (SUCCESS);
	else
		return (FAILURE);
}

void	define_start_and_end(int *start, int *end, int idx, int line_len)
{
	*start = idx - 1;
	if (idx - 1 < 0)
		*start = 0;
	*end = idx + 1;
	if (idx + 1 > line_len - 1)
		*end = line_len - 1;
}

int	check_same_line(char **lines_arr, int current_line, int idx)
{
	int	line_len;
	int	start;
	int	end;

	line_len = ft_strlen(lines_arr[current_line]);
	define_start_and_end(&start, &end, idx, line_len);
	while (start <= end)
	{
		if (!is_valid_space_sorrounding_char(lines_arr[current_line][start]))
			return (FAILURE);
		start++;
	}
	return (SUCCESS);
}
int	check_previous_line(char **lines_arr, int current_line, int first_line,
		int idx)
{
	int	line_len;
	int	start;
	int	end;

	if (current_line == first_line)
		return (SUCCESS);
	line_len = ft_strlen(lines_arr[current_line - 1]);
	define_start_and_end(&start, &end, idx, line_len);
	while (start <= end)
	{
		if (!is_valid_space_sorrounding_char(lines_arr[current_line
				- 1][start]))
			return (FAILURE);
		start++;
	}
	return (SUCCESS);
}

int	check_next_line(char **lines_arr, int current_line, int last_line, int idx)
{
	int	line_len;
	int	start;
	int	end;

	if (current_line == last_line)
		return (SUCCESS);
	line_len = ft_strlen(lines_arr[current_line + 1]);
	define_start_and_end(&start, &end, idx, line_len);
	while (start <= end)
	{
		if (!is_valid_space_sorrounding_char(lines_arr[current_line
				+ 1][start]))
			return (FAILURE);
		start++;
	}
	return (SUCCESS);
}

int	spaces_are_sourrounded_by_walls(char **lines_arr, int current_line,
		int first_line, int last_line)
{
	int	i;

	i = 0;
	while (lines_arr[current_line][i] != '\0')
	{
		if (lines_arr[current_line][i] == ' ')
		{
			if (!check_same_line(lines_arr, current_line, i))
				return (FAILURE);
			if (!check_previous_line(lines_arr, current_line, first_line, i))
				return (FAILURE);
			if (!check_next_line(lines_arr, current_line, last_line, i))
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

void	process_map_content(char **lines_arr, t_data *data, int first_line)
{
	int	i;
	int	map_width;
	int	map_height;
	int	last_line;

	printf("Processing map content...\n");
	i = first_line;
	map_width = ft_strlen(lines_arr[first_line]);
	map_height = calculate_height(lines_arr, first_line);
	last_line = first_line + map_height - 1;
	while (lines_arr[i] != NULL)
	{
		// Check for empty lines
		if (lines_arr[i][0] == '\0')
			perror("Error\nEmpty line in map");
		// Check for invalid characters
		if (!has_only_valid_chars(lines_arr[i]))
			perror("Error\nInvalid character in map");
		// Check for walls
		if (!is_surrounded_by_walls(lines_arr, i, first_line, map_height - 1))
			perror("Error\nMap is not surrounded by walls");
		// Check for spaces
		if (!spaces_are_sourrounded_by_walls(lines_arr, i, first_line,
				last_line))
			perror("Error\nSpaces are not surrounded by walls");
		// Find max width
		map_width = find_max_width(lines_arr, map_width);
		printf("%s\n", lines_arr[i]);
		i++;
	}
	data->map->w_map = map_width;
	data->map->h_map = map_height;
	data->map->grid = malloc(map_height * sizeof(char *));
	if (!data->map->grid)
		error_exit("Error\nMalloc failed", data);
	i = 0;
	while (i < map_height)
	{
		// data->map->grid[i] = malloc(map_width * sizeof(char));
		data->map->grid[i] = ft_calloc(map_width, sizeof(char));
		if (!data->map->grid[i])
			error_exit("Error\nMalloc failed", data);
		ft_strlcpy(data->map->grid[i], lines_arr[first_line + i], map_width
			+ 1);
		i++;
	}
	free_str_arr(lines_arr);
}

void	process_map(char **lines_arr, t_data *data)
{
	t_map_elements	elements;
	int				i;

	// First process map elements ...
	ft_putstr_fd("Processing map elements...\n", 1);
	init_elements_status(&elements);
	i = 0;
	while (lines_arr[i] != NULL)
	{
		printf("while loop n %d\n", i);
		printf("line: %s\n", lines_arr[i]);
		process_map_elements(lines_arr[i], &i, data, &elements);
		if (check_all_elements_found(&elements))
			break ;
		i++;
	}
	ft_putstr_fd("Processing map elements done.\n", 1);
	ft_putstr_fd("The correct number of map elements have been found.\n", 1);
	ft_putstr_fd("The texture paths have been saved§.\n", 1);
	ft_putstr_fd("They are:\n", 1);
	ft_putstr_fd(data->textures_paths->north, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(data->textures_paths->south, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(data->textures_paths->west, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(data->textures_paths->east, 1);
	ft_putstr_fd("\n", 1);
	// Skip empty lines
	while (lines_arr[i] != NULL && lines_arr[i][0] == '\0')
		i++;
	// ... then process map content
	ft_putstr_fd("Processing map content...\n", 1);
	process_map_content(lines_arr, data, i);
}

/* DEBUGGING FUNCTION */

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


