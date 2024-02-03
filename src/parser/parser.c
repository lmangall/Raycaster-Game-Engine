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

	// int		fd;
	// hier the t_map struct should be initialised
	// and it should be 'passed' to data
	if (argc != 2)
		error_exit("Wrong number of arguments. The proper usage is ./cub3D <map.cub>",
			data);
	// open_and_check_file(argv[1], &fd);
	parse_file(argv[1], &lines_arr);
	print_lines_arr(lines_arr);
	process_map(lines_arr, data);
}
