/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_elements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:50:41 by slombard          #+#    #+#             */
/*   Updated: 2024/02/02 01:11:58 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

int	check_identifier(char *line, const char *identifier,
		t_status *element_status, t_data *data)
{
	if (ft_strncmp(line, identifier, ft_strlen(identifier)) == 0)
	{
		if (*element_status == FOUND)
		{
			free_exit_parser(data, "Error: Duplicate identifier");
			return (FAILURE);
		}
		else
		{
			// ft_printf("%s identifier found\n", identifier);
			*element_status = FOUND;
			return (SUCCESS);
		}
	}
	else
	{
		// ft_printf("%s identifier not found\n", identifier);
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
	while (*line == ' ')
		line++;
	if (*line != '\0')
		free_exit_parser(data, "Error: Extra data after identifier");
}

int	char_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (SUCCESS);
	else
		return (FAILURE);
}

int	str_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!char_isdigit(str[i]))
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
		printf("if (i != 3)\n");
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
			printf("if (!str_isdigit(rgb_values[i]))\n");
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
		printf("rgb_values[i]: %s\n", rgb_values[i]);
		rgb[i] = ft_atoi(rgb_values[i]);
		printf("rgb[i]: %d\n", rgb[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			printf("if (rgb[i] < 0 || rgb[i] > 255)\n");
			printf("Error\n");
			printf("Invalid RGB values\n");
			free_str_arr(rgb_values);
			// free whatever was allocated before
			exit(EXIT_FAILURE);
		}
		i++;
	}
	// Skip spaces
	printf("line ptr: %p\n", line);
	if (*line)
		printf("*line: %c\n", *line);
	if (line == NULL)
		printf("line is NULL\n");
	if (*line == '\0')
		printf("*line is \\0\n");
	if (line != NULL)
	{
		while (*line == ' ' && *line != '\0')
			line++;
	}
	// Check for extra data
	if (line != NULL && *line != '\0')
	{
		printf("Error\n");
		printf("Extra data after %s identifier\n", identifier);
		free_str_arr(rgb_values);
		// free whatever was allocated before
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (rgb_values[i] != NULL)
	{
		printf("rgb_values[%d]: %s\n", i, rgb_values[i]);
		i++;
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
			&data->map->textures_paths->north, data);
	else if (ft_strncmp(identifier, "SO", ft_strlen(identifier)) == 0)
		collect_elements_data_path(line, identifier,
			&data->map->textures_paths->south, data);
	else if (ft_strncmp(identifier, "WE", ft_strlen(identifier)) == 0)
		collect_elements_data_path(line, identifier,
			&data->map->textures_paths->west, data);
	else if (ft_strncmp(identifier, "EA", ft_strlen(identifier)) == 0)
		collect_elements_data_path(line, identifier,
			&data->map->textures_paths->east, data);
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

void	process_map_elements_line(char *line, t_data *data,
		t_map_elements_check *elements)
{
	printf("process_map_elements START\n");
	if (line[0] == '\0' || line[0] == '\n')
	{
		printf("Empty line skipped in process_map_elements\n");
		return ;
	}
	while (*line == ' ')
		line++;
	if (check_identifier(line, "NO", &elements->no, data) == SUCCESS)
		collect_elements_data(line, "NO", data);
	else if (check_identifier(line, "SO", &elements->so, data) == SUCCESS)
		collect_elements_data(line, "SO", data);
	else if (check_identifier(line, "WE", &elements->we, data) == SUCCESS)
		collect_elements_data(line, "WE", data);
	else if (check_identifier(line, "EA", &elements->ea, data) == SUCCESS)
		collect_elements_data(line, "EA", data);
	else if (check_identifier(line, "C", &elements->c, data) == SUCCESS)
		collect_elements_data(line, "C", data);
	else if (check_identifier(line, "F", &elements->f, data) == SUCCESS)
		collect_elements_data(line, "F", data);
	else
		error_exit("Invalid identifier");
	printf("process_map_elements END\n");
}
