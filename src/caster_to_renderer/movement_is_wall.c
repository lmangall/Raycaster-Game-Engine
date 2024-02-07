/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_is_wall.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:49:35 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/07 13:12:36 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall_at(t_data *data, int x, int y)
{
	return (data->map->grid[y][x] == '1');
}

static int	is_wall_ahead(t_data *data, double x, double y,
		double buffer_distance)
{
	int	map_ahead_x;
	int	map_ahead_y;

	map_ahead_x = ((x + buffer_distance) / TILE_SIZE);
	map_ahead_y = ((y + buffer_distance) / TILE_SIZE);
	return (is_wall_at(data, map_ahead_x, map_ahead_y));
}

static int	is_wall_right(t_data *data, double x, double y,
		double buffer_distance)
{
	int	map_right_x;
	int	map_right_y;

	map_right_x = ((x + cos(data->player->orientation_angle_rd + M_PI / 2)
				* buffer_distance) / TILE_SIZE);
	map_right_y = ((y + sin(data->player->orientation_angle_rd + M_PI / 2)
				* buffer_distance) / TILE_SIZE);
	return (is_wall_at(data, map_right_x, map_right_y));
}

static int	is_wall_left(t_data *data, double x, double y,
		double buffer_distance)
{
	int	map_left_x;
	int	map_left_y;

	map_left_x = ((x + cos(data->player->orientation_angle_rd - M_PI / 2)
				* buffer_distance) / TILE_SIZE);
	map_left_y = ((y + sin(data->player->orientation_angle_rd - M_PI / 2)
				* buffer_distance) / TILE_SIZE);
	return (is_wall_at(data, map_left_x, map_left_y));
}

int	is_wall(t_data *data, double x, double y)
{
	int		new_position_x;
	int		new_position_y;
	double	buffer_distance;

	buffer_distance = PLAYER_TRANSLATION_SPEED * 0.2;
	new_position_x = (x / TILE_SIZE);
	new_position_y = (y / TILE_SIZE);
	if (is_wall_at(data, new_position_x, new_position_y))
		return (1);
	if (is_wall_ahead(data, x, y, buffer_distance))
		return (1);
	if (is_wall_right(data, x, y, buffer_distance))
		return (1);
	if (is_wall_left(data, x, y, buffer_distance))
		return (1);
	return (0);
}
