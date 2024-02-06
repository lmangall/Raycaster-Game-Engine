/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:17:53 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/06 12:00:10 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

static void	update_length_and_collision_orientation(t_data *data)
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
