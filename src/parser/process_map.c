/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:49:28 by slombard          #+#    #+#             */
/*   Updated: 2024/02/02 02:32:57 by slombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

int	all_elements_found(t_map_elements_check *elements)
{
	ft_printf("Checking if all elements have been found...\n");
	if (elements->no == FOUND && elements->so == FOUND && elements->we == FOUND
		&& elements->ea == FOUND && elements->c == FOUND
		&& elements->f == FOUND)
	{
		ft_printf("All elements found\n");
		return (SUCCESS);
	}
	else
	{
		ft_printf("Not all elements found\n");
		return (FAILURE);
	}
}

void	process_map_elements(char **lines_arr, int *i, t_map *map, t_data *data)
{
	while (lines_arr[*i] != NULL)
	{
		process_map_elements_line(lines_arr[*i], data, &map->elements);
		print_elements_status(&map->elements);
		if (all_elements_found(&map->elements) == SUCCESS)
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
}
