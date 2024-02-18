/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:18:29 by slombard          #+#    #+#             */
/*   Updated: 2024/02/18 16:17:36 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

// The message says 'seems to be empty or incomplete' because
// we perform this check at the beginning and after
// processing the map elements, so we can't be sure if the map
// is empty or incomplete at this point.
// For a most customized message, we should add a flag

void	skip_empty_lines(char **lines_arr, int *i)
{
	int	j;

	while (lines_arr[*i] != NULL)
	{
		j = 0;
		while (ft_isspace(lines_arr[*i][j]))
			j++;
		if (lines_arr[*i][j] != '\0')
			break ;
		(*i)++;
	}
	if (lines_arr[*i] == NULL)
	{
		free_str_arr(lines_arr);
		error_exit("The map seems to be empty or incomplete!");
	}
}

void	process_map(char **lines_arr, t_map *map, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	skip_empty_lines(lines_arr, &i);
	process_map_elements(lines_arr, &i, map, data);
	if (data->debug == ALL)
		print_map_elements(data);
	while (lines_arr[i] != NULL)
	{
		j = 0;
		while (lines_arr[i][j] != '\0')
		{
			if (!ft_isspace(lines_arr[i][j]))
				break ;
			j++;
		}
		if (lines_arr[i][j] != '\0')
			break ;
		i++;
	}
	skip_empty_lines(lines_arr, &i);
	process_map_content(lines_arr, i, data);
}

// Todo: refactor following DRY
void	check_texture_paths(t_data *data)
{
	if (open(data->map->textures_paths->north, O_RDONLY) == -1)
		free_exit_parser(data, "Wrong texture path");
	if (open(data->map->textures_paths->south, O_RDONLY) == -1)
		free_exit_parser(data, "Wrong texture path");
	if (open(data->map->textures_paths->west, O_RDONLY) == -1)
		free_exit_parser(data, "Wrong texture path");
	if (open(data->map->textures_paths->east, O_RDONLY) == -1)
		free_exit_parser(data, "Wrong texture path");
}

uint32_t	rgba_to_int(t_rgba color)
{
	return (color.r << 24 | color.g << 16 | color.b << 8 | 255);
}

void	parser(int argc, char **argv, t_data *data)
{
	char	**lines_arr;
	t_map	*map;

	lines_arr = NULL;
	if (argc != 2)
		error_exit("Wrong number of arguments. Usage is ./cub3D <map.cub>");
	parse_file(argv[1], &lines_arr);
	map = ft_calloc(1, sizeof(t_map));
	map = init_map(map);
	data->map = map;
	data->map->lines_arr = lines_arr;
	if (data->debug == ALL)
		print_lines_arr(lines_arr);
	process_map(lines_arr, map, data);
	check_texture_paths(data);
	if (data->debug == ALL || data->debug == ONLY_FINAL)
		print_map_final(data);
	data->map->c_color = rgba_to_int(data->map->c);
	data->map->f_color = rgba_to_int(data->map->f);
}
