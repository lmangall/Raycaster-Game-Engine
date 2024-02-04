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
			*element_status = FOUND;
			return (SUCCESS);
		}
	}
	else
		return (FAILURE);
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
