/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:16:58 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/06 12:13:10 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(t_data *data, double x, double y)
{
	int	map_grid_y;
	int	map_grid_x;

	map_grid_x = (int)(x / TILE_SIZE);
	map_grid_y = (int)(y / TILE_SIZE);
	if (map_grid_y < 0 || map_grid_y >= data->map->height || map_grid_x < 0
		|| map_grid_x >= data->map->width)
	{
		return (1);
	}
	return (data->map->grid[map_grid_y][map_grid_x] == '1');
}
