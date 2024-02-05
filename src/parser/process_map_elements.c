

#include "cub3d.h"
#include "parser.h"

int	all_elements_found(t_map_elements_check *elements)
{
	if (elements->no == FOUND && elements->so == FOUND && elements->we == FOUND
		&& elements->ea == FOUND && elements->c == FOUND
		&& elements->f == FOUND)
	{
		return (SUCCESS);
	}
	else
	{
		return (FAILURE);
	}
}

void	collect_elements_data_path(char *line, char *identifier, char **target,
		t_data *data)
{
	char	*start;
	char	*end;

	while (*line == ' ')
		line++;
	line += ft_strlen(identifier);
	while (*line == ' ')
		line++;
	start = line;
	while (*line != ' ' && *line != '\0')
		line++;
	end = line;
	*target = ft_substr(start, 0, end - start);
	if (!*target)
		free_exit_parser(data, "Malloc failed");
	while (*line == ' ')
		line++;
	if (*line == '\0')
		return ;
	else
		free_exit_parser(data, "Extra data after Path identifier");
}

int	check_identifier(char *line, const char *identifier,
		t_status *element_status, t_data *data)
{
	if (ft_strncmp(line, identifier, ft_strlen(identifier)) == 0)
	{
		if (*element_status == FOUND)
		{
			free_exit_parser(data, "Duplicate identifier");
			return (FAILURE);
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

void	process_map_elements_line(char *line, t_data *data,
		t_map_elements_check *elements)
{
	if (line[0] == '\0')
		return ;
	while (*line == ' ')
		line++;
	if (check_identifier(line, "NO", &elements->no, data) == SUCCESS)
		collect_elements_data_path(line, "NO",
			&data->map->textures_paths->north, data);
	else if (check_identifier(line, "SO", &elements->so, data) == SUCCESS)
		collect_elements_data_path(line, "SO",
			&data->map->textures_paths->south, data);
	else if (check_identifier(line, "WE", &elements->we, data) == SUCCESS)
		collect_elements_data_path(line, "WE", &data->map->textures_paths->west,
			data);
	else if (check_identifier(line, "EA", &elements->ea, data) == SUCCESS)
		collect_elements_data_path(line, "EA", &data->map->textures_paths->east,
			data);
	else if (check_identifier(line, "C", &elements->c, data) == SUCCESS)
		collect_elements_data_rgba(line, "C", data);
	else if (check_identifier(line, "F", &elements->f, data) == SUCCESS)
		collect_elements_data_rgba(line, "F", data);
	else
		error_exit("Invalid identifier");
}

void	process_map_elements(char **lines_arr, int *i, t_map *map, t_data *data)
{
	while (lines_arr[*i] != NULL)
	{
		process_map_elements_line(lines_arr[*i], data, &map->elements);
		print_elements_status(&map->elements);
		if (all_elements_found(&map->elements) == SUCCESS)
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
}
