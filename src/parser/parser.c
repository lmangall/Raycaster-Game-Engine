/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:18:29 by slombard          #+#    #+#             */
/*   Updated: 2024/01/31 17:18:31 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

void	process_map(char **lines_arr, t_data *data)
{
	t_map	*map;
	int		i;

	map = ft_calloc(1, sizeof(t_map));
	map = init_map(map);
	data->map = map;
	i = 0;
	process_map_elements(lines_arr, &i, map, data);
	if (data->debug == ALL)
		print_map_elements(data);
	while (lines_arr[i] != NULL && (lines_arr[i][0] == '\0'
			|| lines_arr[i][0] == '\n'))
		i++;
	if (data->debug == ALL)
		ft_printf("Processing map content...\n");
	process_map_content(lines_arr, data, i);
	if (data->debug == ALL || data->debug == ONLY_FINAL)
		print_map_final(data);
}

void	parser(int argc, char **argv, t_data *data)
{
	char	**lines_arr;

	if (argc != 2)
		error_exit("Wrong number of arguments. The proper usage is ./cub3D <map.cub>");
	parse_file(argv[1], &lines_arr);
	if (data->debug == ALL)
		print_lines_arr(lines_arr);
	process_map(lines_arr, data);
}