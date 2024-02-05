/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_content_height_width.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 17:18:30 by slombard          #+#    #+#             */
/*   Updated: 2024/02/01 17:18:31 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

// int	line_has_not_only_spaces(char *line, int *i)
// {
// 	while (line[*i] != '\0')
// 	{
// 		if (line[*i] != ' ')
// 			return (SUCCESS);
// 		(*i)++;
// 	}
// 	return (FAILURE);
// }

int	line_has_not_only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!ft_isspace(line[i]))
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

// Enhance calculate height so that it doesn't count empty lines
// empty lines are lines that contain only spaces
// Eventually change the flag empty_line_found with a macro
int	calculate_height(char **lines_arr, int first_line, t_data *data)
{
	int	i;
	int	height;
	int	empty_line_found;

	i = first_line;
	empty_line_found = 0;
	height = 0;
	while (lines_arr[i] != NULL)
	{
		if (line_has_not_only_spaces(lines_arr[i]) == SUCCESS
			&& empty_line_found == 0)
			height++;
		else if (line_has_not_only_spaces(lines_arr[i]) == FAILURE
			&& empty_line_found == 0)
			empty_line_found = 1;
		else if (line_has_not_only_spaces(lines_arr[i]) == SUCCESS
			&& empty_line_found == 1)
			free_exit_parser(data,
				"Content after empty line in map or empty line in a map");
		i++;
	}
	printf("height: %d\n", height);
	return (height);
}

int	find_max_width(char **lines_arr, int current_max_width)
{
	int i;
	int current_width;

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