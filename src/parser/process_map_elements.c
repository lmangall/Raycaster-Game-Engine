/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_elements.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:50:41 by slombard          #+#    #+#             */
/*   Updated: 2024/01/31 19:50:43 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

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

void	process_map_elements(char *line, int *i, t_data *data,
		t_map_elements *elements)
{
	// We increment i in the main loop
	// No need to increment it here
	// Remove it!
	(void)i;
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
	// (*i)++;
	printf("process_map_elements END\n");
}
