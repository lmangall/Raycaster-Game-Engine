/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_collision.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:04:01 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/06 12:08:31 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_collision_adjust_step(float angle, float *inter, float *step,
		char plane)
{
	if (plane == 'y')
	{
		if (ray_direction(angle, 'x') == DOWN)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (ray_direction(angle, 'y') == LEFT)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

int	update_steps_direction(float angle, float *step, char plane)
{
	if (plane == 'x')
	{
		if (ray_direction(angle, plane) == DOWN)
		{
			if (*step < 0)
				*step *= -1;
		}
		else if (*step > 0)
			*step *= -1;
	}
	else if (plane == 'y')
	{
		if (ray_direction(angle, plane) == RIGHT)
		{
			if (*step > 0)
				*step *= -1;
		}
		else
		{
			if (*step < 0)
				*step *= -1;
		}
	}
	return (0);
}

float	find_x_collision(t_data *data, float angl)
{
	float	x;
	float	y;
	float	x_step;
	float	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	angl = normalize_angle(angl);
	y = floor(data->player->y_pos_px / TILE_SIZE) * TILE_SIZE;
	pixel = check_collision_adjust_step(angl, &y, &y_step, 'y');
	x = data->player->x_pos_px + (y - data->player->y_pos_px) / tan(angl);
	update_steps_direction(angl, &x_step, 'y');
	while (wall_hit(x, y - pixel, data))
	{
		x += x_step;
		y += y_step;
	}
	data->ray->horizontal_x = x;
	data->ray->horizontal_y = y;
	return (sqrt(pow(x - data->player->x_pos_px, 2) + pow(y
				- data->player->y_pos_px, 2)));
}

float	find_y_collision(t_data *data, float angl)
{
	float	x;
	float	y;
	float	x_step;
	float	y_step;
	int		pixel;

	x_step = TILE_SIZE;
	y_step = TILE_SIZE * tan(angl);
	angl = normalize_angle(angl);
	x = floor(data->player->x_pos_px / TILE_SIZE) * TILE_SIZE;
	pixel = check_collision_adjust_step(angl, &x, &x_step, 'x');
	y = data->player->y_pos_px + (x - data->player->x_pos_px) * tan(angl);
	update_steps_direction(angl, &y_step, 'x');
	while (wall_hit(x - pixel, y, data))
	{
		x += x_step;
		y += y_step;
	}
	data->ray->vertical_x = x;
	data->ray->vertical_y = y;
	return (sqrt(pow(x - data->player->x_pos_px, 2) + pow(y
				- data->player->y_pos_px, 2)));
}
