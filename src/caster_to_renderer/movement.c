/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:17:05 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/06 17:30:06 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
