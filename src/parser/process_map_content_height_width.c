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