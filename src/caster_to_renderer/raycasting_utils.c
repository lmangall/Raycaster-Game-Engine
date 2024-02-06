/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:17:45 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/06 12:07:35 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ray_direction(float angle, char plane)
{
	if (plane == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (DOWN);
		else
			return (UP);
	}
	else if (plane == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (RIGHT);
		else
			return (LEFT);
	}
	return (0);
}

int	wall_hit(float x, float y, t_data *data)
{
	int	x_position;
	int	y_position;

	if (x < 0 || y < 0)
		return (0);
	x_position = floor(x / TILE_SIZE);
	y_position = floor(y / TILE_SIZE);
	if ((y_position >= data->map->height || x_position >= data->map->width))
		return (0);
	if (data->map->grid[y_position]
		&& x_position <= (int)strlen(data->map->grid[y_position]))
		if (data->map->grid[y_position][x_position] == '1')
			return (0);
	return (1);
}
