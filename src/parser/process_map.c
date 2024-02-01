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

void	print_elements_status(t_map_elements *elements)
{
	if (elements->no == NOT_FOUND)
		printf("NO : NOT_FOUND\n");
	else
		printf("NO : FOUND\n");
	if (elements->so == NOT_FOUND)
		printf("SO : NOT_FOUND\n");
	else
		printf("SO : FOUND\n");
	if (elements->we == NOT_FOUND)
		printf("WE: NOT FOUND\n");
	else
		printf("WE: FOUND\n");
	if (elements->ea == NOT_FOUND)
		printf("EA: NOT FOUND\n");
	else
		printf("EA: FOUND\n");
	if (elements->c == NOT_FOUND)
		printf("C: NOT FOUND\n");
	else
		printf("C: FOUND\n");
	if (elements->f == NOT_FOUND)
		printf("F: NOT FOUND\n");
	else
		printf("F: FOUND\n");
}

void	process_map(char **lines_arr, t_data *data)
{
	t_map_elements		elements;
	t_map				map;
	t_textures_paths	textures_paths;
	int					i;

	// First process map elements ...
	ft_putstr_fd("Processing map elements...\n", 1);
	init_elements_status(&elements);
	init_textures_paths(&textures_paths);
	data->textures_paths = &textures_paths;
	// init_texture_paths(data->textures_paths);
	init_map(&map);
	data->map = &map;
	i = 0;
	while (lines_arr[i] != NULL)
	{
		printf("\n\n\n");
		printf("while loop #%d\n", i + 1);
		printf("line: %s\n", lines_arr[i]);
		process_map_elements(lines_arr[i], &i, data, &elements);
		print_elements_status(&elements);
		if (all_elements_found(&elements) == SUCCESS)
		{
			printf("All elements found\n");
			printf("We break!\n");
			i++;
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
	ft_putstr_fd("C: ", 1);
	ft_putnbr_fd(data->map->c.r, 1);
	ft_putstr_fd(", ", 1);
	ft_putnbr_fd(data->map->c.g, 1);
	ft_putstr_fd(", ", 1);
	ft_putnbr_fd(data->map->c.b, 1);
	ft_putstr_fd(", ", 1);
	ft_putnbr_fd(data->map->c.a, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("F: ", 1);
	ft_putnbr_fd(data->map->f.r, 1);
	ft_putstr_fd(", ", 1);
	ft_putnbr_fd(data->map->f.g, 1);
	ft_putstr_fd(", ", 1);
	ft_putnbr_fd(data->map->f.b, 1);
	ft_putstr_fd(", ", 1);
	ft_putnbr_fd(data->map->f.a, 1);
	ft_putstr_fd("\n", 1);
	// Skip empty lines
	printf("lines_arr[%d]: %s before skipping empty lines\n", i, lines_arr[i]);
	while (lines_arr[i] != NULL && (lines_arr[i][0] == '\0'
			|| lines_arr[i][0] == '\n'))
	{
		printf("lines_arr[%d]: %s\n", i, lines_arr[i]);
		printf("Skipping empty line\n");
		i++;
	}
	// ... then process map content
	ft_putstr_fd("Processing map content...\n", 1);
	process_map_content(lines_arr, data, i);
}
