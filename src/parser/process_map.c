/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:49:28 by slombard          #+#    #+#             */
/*   Updated: 2024/02/04 11:59:10 by lmangall         ###   ########.fr       */
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
	printf("Checking if all elements have been found...\n");
	if (elements->no == FOUND && elements->so == FOUND && elements->we == FOUND
		&& elements->ea == FOUND && elements->c == FOUND
		&& elements->f == FOUND)
	{
		printf("All elements found\n");
		return (SUCCESS);
	}
	else
	{
		printf("Not all elements found\n");
		return (FAILURE);
	}
}

void	process_map(char **lines_arr, t_data *data)
{
	t_map_elements	elements;
	t_map			*map;
	int				i;

	printf("Processing map elements...\n");
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
