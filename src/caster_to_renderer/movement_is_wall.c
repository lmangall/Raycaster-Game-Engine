/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_is_wall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:49:35 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/07 13:07:08 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define BUFFER_DISTANCE (MOVEMENT_SPEED * 0.2)

static int	is_wall_at(t_data *data, int x, int y)
{
	return (data->map->grid[y][x] == '1');
}

static int	is_wall_ahead(t_data *data, double x, double y)
{
	int	map_ahead_x;
	int	map_ahead_y;

	map_ahead_x = ((x + BUFFER_DISTANCE) / TILE_SIZE);
	map_ahead_y = ((y + BUFFER_DISTANCE) / TILE_SIZE);
	return (is_wall_at(data, map_ahead_x, map_ahead_y));
}

static int	is_wall_right(t_data *data, double x, double y)
{
	int	map_right_x;
	int	map_right_y;

	map_right_x = ((x + cos(data->player->orientation_angle_rd + M_PI / 2)
				* BUFFER_DISTANCE) / TILE_SIZE);
	map_right_y = ((y + sin(data->player->orientation_angle_rd + M_PI / 2)
				* BUFFER_DISTANCE) / TILE_SIZE);
	return (is_wall_at(data, map_right_x, map_right_y));
}

static int	is_wall_left(t_data *data, double x, double y)
{
	int	map_left_x;
	int	map_left_y;

	map_left_x = ((x + cos(data->player->orientation_angle_rd - M_PI / 2)
				* BUFFER_DISTANCE) / TILE_SIZE);
	map_left_y = ((y + sin(data->player->orientation_angle_rd - M_PI / 2)
				* BUFFER_DISTANCE) / TILE_SIZE);
	return (is_wall_at(data, map_left_x, map_left_y));
}

/**
 * @brief Checks if there is a wall at the player's new position, ahead,
 * to the right, or to the left.
 * @param data Pointer to the game data structure,
 *which includes the player's position and orientation, and the game map.
 * @param x The x-coordinate of the player's new position.
 * @param y The y-coordinate of the player's new position.
 * @return int Returns 1 if there's a wall at the new position, ahead,
 *to the right, or to the left. Returns 0 otherwise.
 */
int	is_wall(t_data *data, double x, double y)
{
	int	new_position_x;
	int	new_position_y;

	new_position_x = (x / TILE_SIZE);
	new_position_y = (y / TILE_SIZE);
	if (is_wall_at(data, new_position_x, new_position_y))
		return (1);
	if (is_wall_ahead(data, x, y))
		return (1);
	if (is_wall_right(data, x, y))
		return (1);
	if (is_wall_left(data, x, y))
		return (1);
	return (0);
}

// #include "cub3d.h"

// #define DISTANCE_RATIO 0.2

// static int	is_wall_at(t_data *data, int x, int y)
// {
// 	return (data->map->grid[y][x] == '1');
// }

// static int	is_wall_ahead(t_data *data, double x, double y)
// {
// 	int	map_ahead_x;
// 	int	map_ahead_y;

// 	map_ahead_x = ((x + (MOVEMENT_SPEED * DISTANCE_RATIO) / TILE_SIZE));
// 	map_ahead_y = ((y + (MOVEMENT_SPEED * DISTANCE_RATIO)) / TILE_SIZE);
// 	return (is_wall_at(data, map_ahead_x, map_ahead_y));
// }

// static int	is_wall_right(t_data *data, double x, double y)
// {
// 	int	map_right_x;
// 	int	map_right_y;

// 	map_right_x = ((x + cos(data->player->orientation_angle_rd + M_PI / 2)
// 				* (MOVEMENT_SPEED * DISTANCE_RATIO)) / TILE_SIZE);
// 	map_right_y = ((y + sin(data->player->orientation_angle_rd + M_PI / 2)
// 				* (MOVEMENT_SPEED * DISTANCE_RATIO)) / TILE_SIZE);
// 	return (is_wall_at(data, map_right_x, map_right_y));
// }

// static int	is_wall_left(t_data *data, double x, double y)
// {
// 	int	map_left_x;
// 	int	map_left_y;

// 	map_left_x = ((x + cos(data->player->orientation_angle_rd - M_PI / 2)
// 				* (MOVEMENT_SPEED * DISTANCE_RATIO)) / TILE_SIZE);
// 	map_left_y = ((y + sin(data->player->orientation_angle_rd - M_PI / 2)
// 				* (MOVEMENT_SPEED * DISTANCE_RATIO)) / TILE_SIZE);
// 	return (is_wall_at(data, map_left_x, map_left_y));
// }

// /**
//  * @brief Checks if there is a wall at the player's new position, ahead,
//  * to the right, or to the left.
//  * @param data Pointer to the game data structure,
//  *which includes the player's position and orientation, and the game map.
//  * @param x The x-coordinate of the player's new position.
//  * @param y The y-coordinate of the player's new position.
//  * @return int Returns 1 if there's a wall at the new position, ahead,
//  *to the right, or to the left. Returns 0 otherwise.
//  */
// int	is_wall(t_data *data, double x, double y)
// {
// 	int	new_position_x;
// 	int	new_position_y;

// 	new_position_x = (x / TILE_SIZE);
// 	new_position_y = (y / TILE_SIZE);
// 	if (is_wall_at(data, new_position_x, new_position_y))
// 		return (1);
// 	if (is_wall_ahead(data, x, y))
// 		return (1);
// 	if (is_wall_right(data, x, y))
// 		return (1);
// 	if (is_wall_left(data, x, y))
// 		return (1);
// 	return (0);
// }
