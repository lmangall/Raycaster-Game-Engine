/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:49:35 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/06 20:50:23 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define BUFFER_DISTANCE (PLAYER_TRANSLATION_SPEED * 1.5)

int	is_wall(t_data *data, double x, double y)
{
	int	map_grid_y;
	int	map_grid_x;
	int	map_ahead_x;
	int	map_ahead_y;

	map_grid_x = (x / TILE_SIZE);
	map_grid_y = (y / TILE_SIZE);
	map_ahead_x = ((x + BUFFER_DISTANCE) / TILE_SIZE);
	map_ahead_y = ((y + BUFFER_DISTANCE) / TILE_SIZE);
	if (data->map->grid[map_grid_y][map_grid_x] == '1'
		|| data->map->grid[map_ahead_y][map_ahead_x] == '1'
		|| (data->map->grid[map_grid_y][data->player->x_pos_px
			/ TILE_SIZE] == '1' || data->map->grid[data->player->y_pos_px
			/ TILE_SIZE][map_grid_x] == '1'))
		return (1);
	return (0);
}

// #define SAFETY_DISTANCE 28

// int	is_wall(t_data *data, double x, double y)
// {
// 	int	map_grid_y;
// 	int	map_grid_x;
// 	int	buffer;

// 	buffer = SAFETY_DISTANCE / TILE_SIZE;
// 	map_grid_x = (x / TILE_SIZE);
// 	map_grid_y = (y / TILE_SIZE);
// 	if (data->map->grid[map_grid_y + buffer][map_grid_x + buffer] == '1'
// 		|| data->map->grid[map_grid_y - buffer][map_grid_x - buffer] == '1'
// 		|| data->map->grid[map_grid_y + buffer][data->player->x_pos_px
// 		/ TILE_SIZE] == '1' || data->map->grid[data->player->y_pos_px
// 		/ TILE_SIZE][map_grid_x + buffer] == '1' || data->map->grid[map_grid_y
// 		- buffer][data->player->x_pos_px / TILE_SIZE] == '1'
// 		|| data->map->grid[data->player->y_pos_px / TILE_SIZE][map_grid_x
// 		- buffer] == '1')
// 		return (1);
// 	return (0);
// }
