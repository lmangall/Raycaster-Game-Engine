/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:16:51 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/06 11:16:55 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	key_pressed(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		free_exit(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		data->player->longitudinal_move = FORWARD;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		data->player->longitudinal_move = BACKWARD;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		data->player->lateral_move = L_LEFT;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		data->player->lateral_move = L_RIGHT;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player->rotation = R_LEFT;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player->rotation = R_RIGHT;
}

void	key_released(t_data *data)
{
	if (!mlx_is_key_down(data->mlx, MLX_KEY_W) && !mlx_is_key_down(data->mlx,
			MLX_KEY_S))
		data->player->longitudinal_move = NONE;
	if (!mlx_is_key_down(data->mlx, MLX_KEY_A) && !mlx_is_key_down(data->mlx,
			MLX_KEY_D))
		data->player->lateral_move = L_NONE;
	if (!mlx_is_key_down(data->mlx, MLX_KEY_LEFT) && !mlx_is_key_down(data->mlx,
			MLX_KEY_RIGHT))
		data->player->rotation = R_NONE;
}

void	key_hook(void *tmp)
{
	t_data	*data;

	data = (t_data *)tmp;
	key_pressed(data);
	key_released(data);
	apply_movement(data, 0, 0);
}
