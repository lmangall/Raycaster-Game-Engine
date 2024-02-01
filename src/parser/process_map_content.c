/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_content.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:51:01 by slombard          #+#    #+#             */
/*   Updated: 2024/01/31 19:51:03 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

/* Process map contant */
int	has_only_valid_chars(char *line)
{
	int	i;

	// printf("has_only_valid_chars\n");
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'W' && line[i] != 'E')
		{
			printf("Found invalid character\n");
			printf("line[%d]: %c\n", i, line[i]);
			if (line[i] == '\n')
				printf("line[%d]: \\n\n", i);
			if (line[i] == '\0')
				printf("line[%d]: \\0\n", i);
			return (FAILURE);
		}
		i++;
	}
	// printf("No invalid characters found\n");
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
			{
				printf("check_same_line\n");
				return (FAILURE);
			}
			if (!check_previous_line(lines_arr, current_line, first_line, i))
			{
				printf("check_previous_line\n");
				return (FAILURE);
			}
			if (!check_next_line(lines_arr, current_line, last_line, i))
			{
				printf("check_next_line\n");
				return (FAILURE);
			}
		}
		i++;
	}
	printf("return (SUCCESS)\n");
	return (SUCCESS);
}

void	remove_new_line_char(char **lines_arr, int i)
{
	int		j;
	char	*tmp;

	j = 0;
	while (lines_arr[i][j] != '\0')
	{
		if (lines_arr[i][j] == '\n' && lines_arr[i][j + 1] == '\0')
		{
			tmp = ft_substr(lines_arr[i], 0, j);
			free(lines_arr[i]);
			lines_arr[i] = tmp;
			return ;
		}
		j++;
	}
}

void	process_map_content(char **lines_arr, t_data *data, int first_line)
{
	int	i;
	int	map_width;
	int	map_height;
	int	last_line;

	printf("process_map_content\n");
	i = first_line;
	printf("i: %d\n", i);
	map_width = ft_strlen(lines_arr[first_line]);
	map_height = calculate_height(lines_arr, first_line);
	last_line = first_line + map_height - 1;
	while (lines_arr[i] != NULL)
	{
		remove_new_line_char(lines_arr, i);
		printf("loop #%d\n", i - first_line);
		printf("lines_arr[%d]: %s\n", i - first_line, lines_arr[i]);
		// Check for empty lines
		if (lines_arr[i][0] == '\0')
			perror("Error\nEmpty line in map");
		// Check for invalid characters
		if (has_only_valid_chars(lines_arr[i]) == FAILURE)
			perror("Error\nInvalid character in map");
		// Check for walls
		if (is_surrounded_by_walls(lines_arr, i, first_line, map_height
				- 1) == FAILURE)
			perror("Error\nMap is not surrounded by walls");
		// Check for spaces
		// The readibility of this function is not good
		// In comparison to the other functions
		// But if we just negate it it will not work
		if (spaces_are_sourrounded_by_walls(lines_arr, i, first_line,
				last_line) == FAILURE)
			perror("Error\nSpaces are not surrounded by walls");
		// Find max width
		map_width = find_max_width(lines_arr, map_width);
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
