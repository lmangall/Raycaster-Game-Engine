/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_apply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:16:43 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/06 17:52:45 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define SAFETY_DISTANCE 1

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

static void	move_player_forward(t_data *data, double move_x, double move_y)
{
	move_x = cos(data->player->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
	move_y = sin(data->player->orientation_angle_rd) * PLAYER_TRANSLATION_SPEED;
	if (!is_wall_safe(data, (move_x + data->player->x_pos_px), (move_y
				+ data->player->y_pos_px)))
	{
		data->player->x_pos_px = roundf(data->player->x_pos_px + move_x);
		data->player->y_pos_px = roundf(data->player->y_pos_px + move_y);
	}
}

static void	move_player_backward(t_data *data, double move_x, double move_y)
{
	move_x = -cos(data->player->orientation_angle_rd)
		* PLAYER_TRANSLATION_SPEED;
	move_y = -sin(data->player->orientation_angle_rd)
		* PLAYER_TRANSLATION_SPEED;
	if (!is_wall(data, (data->player->x_pos_px - move_x),
			(data->player->y_pos_px - move_y)))
	{
		data->player->x_pos_px = roundf(data->player->x_pos_px - move_x);
		data->player->y_pos_px = roundf(data->player->y_pos_px - move_y);
	}
}

static void	move_player_lateral(t_data *data, double move_x, double move_y)
{
	if (data->player->lateral_move == L_LEFT)
	{
		move_x = sin(data->player->orientation_angle_rd)
			* PLAYER_TRANSLATION_SPEED;
		move_y = -cos(data->player->orientation_angle_rd)
			* PLAYER_TRANSLATION_SPEED;
	}
	else if (data->player->lateral_move == L_RIGHT)
	{
		move_x = -sin(data->player->orientation_angle_rd)
			* PLAYER_TRANSLATION_SPEED;
		move_y = cos(data->player->orientation_angle_rd)
			* PLAYER_TRANSLATION_SPEED;
	}
	if (!is_wall(data, (move_x + data->player->x_pos_px), (move_y
				+ data->player->y_pos_px)))
	{
		data->player->x_pos_px = roundf(data->player->x_pos_px + move_x);
		data->player->y_pos_px = roundf(data->player->y_pos_px + move_y);
	}
}

void	apply_movement(t_data *data, double move_x, double move_y)
{
	if (data->player->rotation == R_RIGHT)
		rotate_player(&data->player->orientation_angle_rd, R_RIGHT);
	else if (data->player->rotation == R_LEFT)
		rotate_player(&data->player->orientation_angle_rd, R_LEFT);
	if (data->player->lateral_move == L_RIGHT)
		move_player_lateral(data, move_x, move_y);
	else if (data->player->lateral_move == L_LEFT)
		move_player_lateral(data, move_x, move_y);
	else if (data->player->longitudinal_move == FORWARD)
		move_player_forward(data, move_x, move_y);
	else if (data->player->longitudinal_move == BACKWARD)
		move_player_backward(data, move_x, move_y);
}
