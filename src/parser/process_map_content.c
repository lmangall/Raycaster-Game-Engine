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

int	has_only_one_player(char *line)
{
	int	i;
	int	player_count;

	i = 0;
	player_count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
			player_count++;
		i++;
	}
	if (player_count > 1)
		return (FAILURE);
	return (SUCCESS);
}

void	check_lines(char **lines_arr, int *i, t_data *data, int first_line,
		int last_line)
{
	remove_new_line_char(lines_arr, *i, data);
	if (lines_arr[*i][0] == '\0')
		free_exit_parser(data, "Empty line in map");
	if (line_has_not_only_spaces(lines_arr[*i], i) == FAILURE)
		free_exit_parser(data, "Empty (only space) line in map");
	if (has_only_valid_chars(lines_arr[*i]) == FAILURE)
		free_exit_parser(data, "Invalid character in map");
	if (has_only_one_player(lines_arr[*i]) == FAILURE)
		free_exit_parser(data, "Multiple players on the same line");
	if (is_surrounded_by_walls(lines_arr, *i, first_line, data->map->height
			- 1) == FAILURE)
		free_exit_parser(data, "Map is not surrounded by walls");
	if (spaces_are_surrounded_by_walls(lines_arr, *i, first_line,
			last_line) == FAILURE)
		free_exit_parser(data, "Spaces are not surrounded by walls");
}

void	build_grid(t_data *data, char **lines_arr, int first_line)
{
	int	i;

	i = 0;
	data->map->grid = ft_calloc(data->map->height + 1, sizeof(char *));
	if (!data->map->grid)
		free_exit_parser(data, "Malloc failed");
	data->map->grid[data->map->height] = NULL;
	while (i < data->map->height)
	{
		data->map->grid[i] = ft_calloc(data->map->width, sizeof(char));
		if (!data->map->grid[i])
			free_exit_parser(data, "Malloc failed");
		ft_strlcpy(data->map->grid[i], lines_arr[first_line + i],
			data->map->width + 1);
		i++;
	}
}

void	process_map_content(char **lines_arr, t_data *data, int first_line)
{
	int	i;
	int	last_line;

	i = first_line;
	data->map->width = ft_strlen(lines_arr[first_line]);
	data->map->height = calculate_height(lines_arr, first_line);
	last_line = first_line + data->map->height - 1;
	while (lines_arr[i] != NULL)
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
