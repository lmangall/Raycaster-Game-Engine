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

void	print_str_arr(char **str_arri, int map_height)
{
	int	i;

	i = 0;
	while (i < map_height)
	{
		printf("%s\n", str_arri[i]);
		i++;
	}
}

void	print_texture_paths(t_textures_paths *textures_paths)
{
	printf("The saved texture paths are:\n");
	printf("textures_paths->north: %s\n", textures_paths->north);
	printf("textures_paths->south: %s\n", textures_paths->south);
	printf("textures_paths->west: %s\n", textures_paths->west);
	printf("textures_paths->east: %s\n", textures_paths->east);
}

void	print_ceiling_and_floor(t_rgba *c, t_rgba *f)
{
	printf("The saved ceiling and floor colors are:\n");
	printf("C: %d, %d, %d\n", c->r, c->g, c->b);
	printf("F: %d, %d, %d\n", f->r, f->g, f->b);
}

void	print_map_elements(t_data *data)
{
	printf("Processing map elements done.\n");
	printf("The correct number of map elements have been found.\n");
	print_texture_paths(data->map->textures_paths);
	print_ceiling_and_floor(&data->map->c, &data->map->f);
}

void	final_print(t_data *data)
{
	print_texture_paths(data->map->textures_paths);
	print_ceiling_and_floor(&data->map->c, &data->map->f);
	printf("Parsing is complete!\n");
	if (data->map->player_found == FOUND)
		printf("We have only one player\n");
	printf("The position of the player is: %d, %d\n", data->map->p_x,
		data->map->p_y);
	printf("The orientation of the player is: %c\n",
		data->map->player_orientation);
	printf("The map width is: %d\n", data->map->width);
	printf("The map height is: %d\n", data->map->height);
	printf("The map grid is:\n");
	print_str_arr(data->map->grid, data->map->height);
}

void	process_map(char **lines_arr, t_data *data)
{
	t_map_elements	elements;
	t_map			*map;
	int				i;

	printf("Processing map elements...\n");
	init_elements_status(&elements);
	map = init_map();
	data->map = map;
	i = 0;
	while (lines_arr[i] != NULL)
	{
		process_map_elements(lines_arr[i], &i, data, &elements);
		print_elements_status(&elements);
		if (all_elements_found(&elements) == SUCCESS)
		{
			i++;
			break ;
		}
		i++;
	}
	print_map_elements(data);
	// Skip empty lines
	while (lines_arr[i] != NULL && (lines_arr[i][0] == '\0'
			|| lines_arr[i][0] == '\n'))
		i++;
	// ... then process map content
	ft_putstr_fd("Processing map content...\n", 1);
	process_map_content(lines_arr, data, i);
	final_print(data);
}
