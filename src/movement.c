/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:17:05 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/06 11:17:10 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	rotate_player(double *orientation_angle_rd, enum e_rotation direction)
{
	if (direction == R_RIGHT)
	{
		*orientation_angle_rd += PLAYER_ROTATION_SPEED;
		if (*orientation_angle_rd > 2 * M_PI)
			*orientation_angle_rd -= 2 * M_PI;
	}
	else if (direction == R_LEFT)
	{
		*orientation_angle_rd -= PLAYER_ROTATION_SPEED;
		if (*orientation_angle_rd < 0)
			*orientation_angle_rd += 2 * M_PI;
	}
}

int	is_wall(t_data *data, double x, double y)
{
	int	map_grid_y;
	int	map_grid_x;

	map_grid_x = (x / TILE_SIZE);
	map_grid_y = (y / TILE_SIZE);
	if (data->map->grid[map_grid_y][map_grid_x] == '1'
		|| (data->map->grid[map_grid_y][data->player->x_pos_px
			/ TILE_SIZE] == '1' || data->map->grid[data->player->y_pos_px
			/ TILE_SIZE][map_grid_x] == '1'))
		return (1);
	return (0);
}

void	move_player(t_data *data, double move_x, double move_y)
{
	int	new_x_position;
	int	new_y_position;

	new_x_position = roundf(data->player->x_pos_px + move_x);
	new_y_position = roundf(data->player->y_pos_px + move_y);
	if (!is_wall(data, new_x_position, new_y_position))
	{
		data->player->x_pos_px = new_x_position;
		data->player->y_pos_px = new_y_position;
	}
}
