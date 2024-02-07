/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:49:28 by slombard          #+#    #+#             */
/*   Updated: 2024/02/07 15:23:41 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

void	free_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i] != NULL)
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

int	all_elements_found(t_map_elements *elements)
{
	if (elements->no == FOUND && elements->so == FOUND && elements->we == FOUND
		&& elements->ea == FOUND && elements->c == FOUND
		&& elements->f == FOUND)
	{
		return (SUCCESS);
	}
	else
	{
		return (FAILURE);
	}
}

void	process_map(char **lines_arr, t_data *data)
{
	t_map_elements	elements;
	t_map			*map;
	int				i;

	init_elements_status(&elements);
	map = init_map(map);
	data->map = map;
	i = 0;
	while (lines_arr[i] != NULL)
	{
		process_map_elements(lines_arr[i], &i, data, &elements);
		if (all_elements_found(&elements) == SUCCESS)
		{
			i++;
			break ;
		}
		i++;
	}
	while (lines_arr[i] != NULL && (lines_arr[i][0] == '\0'
		|| lines_arr[i][0] == '\n'))
		i++;
	process_map_content(lines_arr, data, i);
	print_map_final(data);
}
