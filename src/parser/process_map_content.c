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

void	extract_player_position(char *line, int y, t_data *data)
{
	int	x;

	x = 0;
	while (line[x] != '\0')
	{
		if (line[x] == 'N' || line[x] == 'S' || line[x] == 'E'
			|| line[x] == 'W')
		{
			if (data->map->player_found == NOT_FOUND)
			{
				data->map->p_x = x;
				data->map->p_y = y;
				data->map->player_orientation = line[x];
				// Assign player orientation
				data->map->player_found = FOUND;
				return ;
			}
			else
			{
				error_exit("Error: Multiple player positions found.", data);
			}
		}
		x++;
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
		// What if we have a line with only spaces?
		// We should check for that too
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
		if (spaces_are_surrounded_by_walls(lines_arr, i, first_line,
				last_line) == FAILURE)
			perror("Error\nSpaces are not surrounded by walls");
		// the function check also if we have more than one player
		// it could have been put inside has_only_valid_chars
		// but it would have made it less readable
		extract_player_position(lines_arr[i], i - first_line, data);
		// Find max width
		map_width = find_max_width(lines_arr, map_width);
		i++;
	}
	if (data->map->player_found == NOT_FOUND)
		perror("Error\nNo player found");
	data->map->width = map_width;
	data->map->height = map_height;
	printf("map_height before: %d\n", map_height);
	// data->map->grid = malloc(map_height * sizeof(char *));
	data->map->grid = ft_calloc(map_height + 1, sizeof(char *));
	if (!data->map->grid)
		error_exit("Error\nMalloc failed", data);
	data->map->grid[map_height] = NULL;
	i = 0;
	printf("i: %d\n", i);
	printf("map_height: %d\n", map_height);
	while (i < map_height)
	{
		// data->map->grid[i] = malloc(map_width * sizeof(char));
		data->map->grid[i] = ft_calloc(map_width, sizeof(char));
		if (!data->map->grid[i])
			error_exit("Error\nMalloc failed", data);
		ft_strlcpy(data->map->grid[i], lines_arr[first_line + i], map_width
			+ 1);
		printf("data->map->grid[%d]: %s\n", i, data->map->grid[i] );
		i++;
	}
	free_str_arr(lines_arr);
}
