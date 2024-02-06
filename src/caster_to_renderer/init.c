/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:16:04 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/06 22:37:27 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	load_textures(data);
	data->ray = calloc(1, sizeof(t_ray));
	data->player = calloc(1, sizeof(t_player));
	init_player(data);
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", 0);
}

void	init_player(t_data *data)
{
	data->player->x_pos_px = data->map->p_x * TILE_SIZE + TILE_SIZE / 2;
	data->player->y_pos_px = data->map->p_y * TILE_SIZE + TILE_SIZE / 2;
	data->player->fov_rd = (FOV * M_PI) / 180;
	data->player->orientation_angle_rd = M_PI;
	data->player->lateral_move = 0;
	data->player->rotation = 0;
	data->player->longitudinal_move = 0;
	init_player_original_orientation(data);
}

void	init_player_original_orientation(t_data *data)
{
	if (data->map->player_orientation == 'N')
		data->player->orientation_angle_rd = 3 * M_PI_2;
	else if (data->map->player_orientation == 'S')
		data->player->orientation_angle_rd = M_PI_2;
	else if (data->map->player_orientation == 'E')
		data->player->orientation_angle_rd = 0;
	else if (data->map->player_orientation == 'W')
		data->player->orientation_angle_rd = M_PI;
	data->ray->angle_rd = data->player->orientation_angle_rd
		- (data->player->fov_rd / 2);
}
