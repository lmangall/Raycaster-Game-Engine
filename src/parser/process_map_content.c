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

void	check_lines(char **lines_arr, int *i, t_data *data, int first_line,
		int last_line)
{
	if (has_only_valid_chars(lines_arr[*i]) == FAILURE)
		free_exit_parser(data, "Invalid character in map");
	if (has_only_one_player(lines_arr[*i]) == FAILURE)
		free_exit_parser(data, "Multiple players on the same line");
	if (is_surrounded_by_walls(lines_arr, *i, first_line, first_line
			+ data->map->height) == FAILURE)
		free_exit_parser(data, "Map is not surrounded by walls");
	if (spaces_are_surrounded_by_walls(lines_arr, *i, first_line,
			last_line) == FAILURE)
		free_exit_parser(data, "Spaces are not surrounded by walls");
}

void	build_grid(t_data *data, char **lines_arr, int first_line)
{
	int		i;
	size_t	line_len;

	i = 0;
	data->map->grid = ft_calloc(data->map->height + 1, sizeof(char *));
	if (!data->map->grid)
		free_exit_parser(data, "Malloc failed");
	data->map->grid[data->map->height] = NULL;
	while (i < data->map->height)
	{
		data->map->grid[i] = ft_calloc(data->map->width + 1, sizeof(char));
		if (!data->map->grid[i])
			free_exit_parser(data, "Malloc failed");
		line_len = ft_strlen(lines_arr[first_line + i]);
		if (line_len > 0 && lines_arr[first_line + i][line_len - 1] == '\n')
			line_len--;
		ft_memcpy(data->map->grid[i], lines_arr[first_line + i], line_len);
		i++;
	}
}

void	process_map_content(char **lines_arr, int first_line, t_data *data)
{
	int	i;
	int	last_line;

	i = first_line;
	data->map->width = ft_strlen(lines_arr[first_line]);
	data->map->height = calculate_height(lines_arr, first_line, data);
	last_line = first_line + data->map->height - 1;
	while (lines_arr[i] != NULL && i < last_line)
	{
		check_lines(lines_arr, &i, data, first_line, last_line);
		extract_player_position(lines_arr[i], i - first_line, data);
		data->map->width = find_max_width(lines_arr, data->map->width);
		i++;
	}
	if (data->map->player_found == NOT_FOUND)
		free_exit_parser(data, "No player found");
	build_grid(data, lines_arr, first_line);
}
