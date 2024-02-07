/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:45:02 by slombard          #+#    #+#             */
/*   Updated: 2024/02/07 13:58:37 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "parser.h"

void	init_map_helper(t_map_elements *elements,
		t_textures_paths **textures_paths_ptr)
{
	*textures_paths_ptr = ft_calloc(1, sizeof(t_textures_paths));
	(*textures_paths_ptr)->north = NULL;
	(*textures_paths_ptr)->south = NULL;
	(*textures_paths_ptr)->west = NULL;
	(*textures_paths_ptr)->east = NULL;
	elements->no = NOT_FOUND;
	elements->no = NOT_FOUND;
	elements->so = NOT_FOUND;
	elements->we = NOT_FOUND;
	elements->ea = NOT_FOUND;
	elements->c = NOT_FOUND;
	elements->f = NOT_FOUND;
}

t_map	*init_map(t_map *map)
{
	t_textures_paths	*textures_paths;

	textures_paths = NULL;
	init_map_helper(&map->elements, &textures_paths);
	map->textures_paths = textures_paths;
	map->grid = NULL;
	map->p_x = 0;
	map->p_y = 0;
	map->player_orientation = '0';
	map->player_found = NOT_FOUND;
	map->width = 0;
	map->height = 0;
	map->c.r = 0;
	map->c.g = 0;
	map->c.b = 0;
	map->f.r = 0;
	map->f.g = 0;
	map->f.b = 0;
	return (map);
}

void	init_data_parser(t_data *data)
{
	data->img = NULL;
	data->mlx = NULL;
	data->ray = NULL;
	data->map = NULL;
	data->player = NULL;
	data->textures = NULL;
	data->debug = OFF;
}
