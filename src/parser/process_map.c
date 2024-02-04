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

int	all_elements_found(t_map_elements_check *elements)
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

void	print_elements_status(t_map_elements_check *elements)
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
	printf("C: %d, %d, %d, %d\n", c->r, c->g, c->b, c->a);
	printf("F: %d, %d, %d, %d\n", f->r, f->g, f->b, f->a);
}

void	print_map_elements_check(t_data *data)
{
	printf("Processing map elements done.\n");
	printf("The correct number of map elements have been found.\n");
	print_texture_paths(data->map->textures_paths);
	print_ceiling_and_floor(&data->map->c, &data->map->f);
}

void	print_map_final(t_data *data)
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

void	process_map_elements(char **lines_arr, int *i, t_map *map, t_data *data)
{
	while (lines_arr[*i] != NULL)
	{
		process_map_elements_line(lines_arr[*i], i, data, &map->elements);
		print_elements_status(&map->elements);
		if (all_elements_found(&map->elements) == SUCCESS)
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
}

void	process_map(char **lines_arr, t_data *data)
{
	t_map	*map;
	int		i;

	map = ft_calloc(1, sizeof(t_map));
	map = init_map(map);
	data->map = map;
	i = 0;
	process_map_elements(lines_arr, &i, map, data);
	print_map_elements_check(data);
	while (lines_arr[i] != NULL && (lines_arr[i][0] == '\0'
			|| lines_arr[i][0] == '\n'))
		i++;
	ft_printf("Processing map content...\n");
	process_map_content(lines_arr, data, i);
	print_map_final(data);
}
