/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:17:53 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/17 17:22:52 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_texture_t	*texture_selection(t_data *data)
{
	double	angle;

	angle = data->ray->angle_rd;
	angle = normalize_angle(angle);
	if (data->ray->wall_collision_orientation == HORIZONTAL)
	{
		if (angle >= 0 && angle < M_PI)
			return (data->textures->south);
		else
			return (data->textures->north);
	}
	else
	{
		if (angle > M_PI_2 && angle <= (3 * M_PI_2))
			return (data->textures->west);
		else
			return (data->textures->east);
	}
}

void	update_ray(t_data *data)
{
	double	wall_h;
	double	wall_bot_pixel;
	double	wall_top_pixel;

	data->ray->length *= cos(normalize_angle(data->ray->angle_rd
				- data->player->orientation_angle_rd));
	wall_h = (TILE_SIZE / data->ray->length) * ((WINDOW_WIDTH / 2)
			/ tan(data->player->fov_rd / 2));
	wall_bot_pixel = (WINDOW_HEIGHT / 2) + (wall_h / 2);
	wall_top_pixel = (WINDOW_HEIGHT / 2) - (wall_h / 2);
	if (wall_bot_pixel > WINDOW_HEIGHT)
		wall_bot_pixel = WINDOW_HEIGHT;
	if (wall_top_pixel < 0)
		wall_top_pixel = 0;
	data->ray->current_texture = texture_selection(data);
	data->ray->wall_h = wall_h;
	data->ray->wall_top_pixel = wall_top_pixel;
	data->ray->wall_bot_pixel = wall_bot_pixel;
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

void	raycasting(void *tmp)
{
	t_data	*data;

	data = (t_data *)tmp;
	data->ray->screen_x = 0;
	data->ray->angle_rd = data->player->orientation_angle_rd
		- (data->player->fov_rd / 2);
	while (data->ray->screen_x < WINDOW_WIDTH)
	{
		// data->ray->wall_collision_orientation = NO_COLLISION;
		update_length_and_collision_orientation(data);
		update_ray(data);
		render_wall_and_background(data);
		data->ray->screen_x++;
		data->ray->angle_rd += (data->player->fov_rd / WINDOW_WIDTH);
	}
}
