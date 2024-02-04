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

void	remove_new_line_char(char **lines_arr, int i, t_data *data)
{
	int		j;
	char	*tmp;

	j = 0;
	while (lines_arr[i][j] != '\0')
	{
		if (lines_arr[i][j] == '\n' && lines_arr[i][j + 1] == '\0')
		{
			tmp = ft_substr(lines_arr[i], 0, j);
			if (!tmp)
				free_exit_parser(data, "Malloc failed");
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
				data->map->player_found = FOUND;
				return ;
			}
			else
				free_exit_parser(data,
					"Error: Multiple player positions found.");
		}
		x++;
	}
}

int	line_has_not_only_spaces(char *line, int *i)
{
	while (line[*i] != '\0')
	{
		if (line[*i] != ' ')
			return (SUCCESS);
		(*i)++;
	}
	return (FAILURE);
}

void	process_map_content(char **lines_arr, t_data *data, int first_line)
{
	int	i;
	int	map_width;
	int	map_height;
	int	last_line;

	i = first_line;
	map_width = ft_strlen(lines_arr[first_line]);
	map_height = calculate_height(lines_arr, first_line);
	last_line = first_line + map_height - 1;
	while (lines_arr[i] != NULL)
	{
		remove_new_line_char(lines_arr, i, data);
		if (lines_arr[i][0] == '\0')
			free_exit_parser(data, "Empty line in map");
		if (line_has_not_only_spaces(lines_arr[i], &i) == FAILURE)
			free_exit_parser(data, "Empty (only space) line in map");
		if (has_only_valid_chars(lines_arr[i]) == FAILURE)
			free_exit_parser(data, "Invalid character in map");
		if (is_surrounded_by_walls(lines_arr, i, first_line, map_height
				- 1) == FAILURE)
			free_exit_parser(data, "Map is not surrounded by walls");
		if (spaces_are_surrounded_by_walls(lines_arr, i, first_line,
				last_line) == FAILURE)
			free_exit_parser(data, "Spaces are not surrounded by walls");
		extract_player_position(lines_arr[i], i - first_line, data);
		map_width = find_max_width(lines_arr, map_width);
		i++;
	}
	if (data->map->player_found == NOT_FOUND)
		free_exit_parser(data, "No player found");
	data->map->width = map_width;
	data->map->height = map_height;
	printf("map_height before: %d\n", map_height);
	data->map->grid = ft_calloc(map_height + 1, sizeof(char *));
	if (!data->map->grid)
		free_exit_parser(data, "Malloc failed");
	data->map->grid[map_height] = NULL;
	i = 0;
	while (i < map_height)
	{
		data->map->grid[i] = ft_calloc(map_width, sizeof(char));
		if (!data->map->grid[i])
			free_exit_parser(data, "Malloc failed");
		ft_strlcpy(data->map->grid[i], lines_arr[first_line + i], map_width
			+ 1);
		i++;
	}
	free_str_arr(lines_arr);
}
