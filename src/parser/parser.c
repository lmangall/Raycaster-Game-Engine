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

void	parser(int argc, char **argv, t_data *data)
{
	char	**lines_arr;

	if (argc != 2)
		error_exit("Wrong number of arguments. The proper usage is ./cub3D <map.cub>",
			data);
	parse_file(argv[1], &lines_arr);
	if (data->debug == ALL)
		print_lines_arr(lines_arr);
	process_map(lines_arr, data);
}
