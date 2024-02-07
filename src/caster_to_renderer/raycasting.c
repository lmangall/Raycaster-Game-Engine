/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:17:53 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/07 14:00:00 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_texture_t	*texture_selection(t_data *data)
{
	double	angle;

	angle = data->ray->angle_rd;
	if (data->ray->wall_collision_orientation == HORIZONTAL)
	{
		if (angle > 0 && angle < M_PI)
			return (data->textures->south);
		else
			return (data->textures->north);
	}
	else
	{
		if (angle > M_PI_2 && angle < (3 * M_PI_2))
			return (data->textures->west);
		else
			return (data->textures->east);
	}
}

void	update_ray(t_data *data)
{
	double	wall_h;
	double	lower_pixel;
	double	higher_pixel;

	data->ray->length *= cos(normalize_angle(data->ray->angle_rd
				- data->player->orientation_angle_rd));
	wall_h = (TILE_SIZE / data->ray->length) * ((WINDOW_WIDTH / 2)
			/ tan(data->player->fov_rd / 2));
	lower_pixel = (WINDOW_HEIGHT / 2) + (wall_h / 2);
	higher_pixel = (WINDOW_HEIGHT / 2) - (wall_h / 2);
	if (lower_pixel > WINDOW_HEIGHT)
		lower_pixel = WINDOW_HEIGHT;
	if (higher_pixel < 0)
		higher_pixel = 0;
	data->ray->current_texture = texture_selection(data);
	data->ray->wall_h = wall_h;
	data->ray->higher_pixel = higher_pixel;
	data->ray->lower_pixel = lower_pixel;
}

void	update_length_and_collision_orientation(t_data *data)
{
	double	x_collision;
	double	y_collision;

	x_collision = find_x_collision(data, data->ray->angle_rd);
	y_collision = find_y_collision(data, data->ray->angle_rd);
	if (y_collision <= x_collision)
	{
		data->ray->length = y_collision;
		data->ray->wall_collision_orientation = VERTICAL;
	}
	else
	{
		data->ray->length = x_collision;
		data->ray->wall_collision_orientation = HORIZONTAL;
	}
}

void	raycasting(t_data *data)
{
	data->ray->screen_x = 0;
	data->ray->angle_rd = data->player->orientation_angle_rd
		- (data->player->fov_rd / 2);
	while (data->ray->screen_x < WINDOW_WIDTH)
	{
		data->ray->wall_collision_orientation = NO_COLLISION;
		update_length_and_collision_orientation(data);
		update_ray(data);
		render_wall(data);
		data->ray->screen_x++;
		data->ray->angle_rd += (data->player->fov_rd / WINDOW_WIDTH);
	}
}
