/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slombard <slombard@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:49:28 by slombard          #+#    #+#             */
/*   Updated: 2024/01/31 19:49:31 by slombard         ###   ########.fr       */
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

void	init_elements_status(t_map_elements *elements)
{
	elements->no = NOT_FOUND;
	elements->so = NOT_FOUND;
	elements->we = NOT_FOUND;
	elements->ea = NOT_FOUND;
	elements->c = NOT_FOUND;
	elements->f = NOT_FOUND;
}

void	process_map(char **lines_arr, t_data *data)
{
	t_map_elements	elements;
	int				i;

	// First process map elements ...
	ft_putstr_fd("Processing map elements...\n", 1);
	init_elements_status(&elements);
	i = 0;
	while (lines_arr[i] != NULL)
	{
		printf("\n\n\n");
		printf("while loop #%d\n", i + 1);
		printf("line: %s\n", lines_arr[i]);
		process_map_elements(lines_arr[i], &i, data, &elements);
		if (all_elements_found(&elements) == SUCCESS)
		{
			printf("All elements found\n");
			printf("We break!\n");
			break ;
		}
		i++;
	}
	ft_putstr_fd("Processing map elements done.\n", 1);
	ft_putstr_fd("The correct number of map elements have been found.\n", 1);
	ft_putstr_fd("The texture paths have been saved§.\n", 1);
	ft_putstr_fd("They are:\n", 1);
	ft_putstr_fd(data->textures_paths->north, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(data->textures_paths->south, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(data->textures_paths->west, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(data->textures_paths->east, 1);
	ft_putstr_fd("\n", 1);
	// Skip empty lines
	while (lines_arr[i] != NULL && lines_arr[i][0] == '\0')
		i++;
	// ... then process map content
	ft_putstr_fd("Processing map content...\n", 1);
	process_map_content(lines_arr, data, i);
}
