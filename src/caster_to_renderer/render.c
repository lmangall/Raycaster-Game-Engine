/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:18:41 by lmangall          #+#    #+#             */
/*   Updated: 2024/02/12 11:06:32 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	adjust_mirroring(double x, double width, double angle, char plane)
{
	int		direction;
	double	adjusted_coordinate;

	direction = ray_direction(angle, plane);
	if ((plane == 'x' && direction == UP) || (plane == 'y'
			&& direction == LEFT))
		adjusted_coordinate = x;
	else
		adjusted_coordinate = width - 1 - x;
	return (adjusted_coordinate);
}

void	determine_plane_and_position(t_data *data, char *plane,
		double *wall_hit_position)
{
	if (data->ray->wall_collision_orientation == HORIZONTAL)
	{
		*plane = 'x';
		*wall_hit_position = data->ray->horizontal_x;
	}
	else
	{
		*plane = 'y';
		*wall_hit_position = data->ray->vertical_y;
	}
	*wall_hit_position = fmod(*wall_hit_position, TILE_SIZE);
}

uint32_t	pixel_color(mlx_texture_t *texture, t_data *data, int wall_top_pixel)
{
	uint32_t	*pixel_array;
	char		plane;
	double		wall_hit_position;
	double		x_pixel_coordinate;
	double		y_pixel_coordinate;

	determine_plane_and_position(data, &plane, &wall_hit_position);
	x_pixel_coordinate = adjust_mirroring((wall_hit_position / TILE_SIZE)
			* texture->width, texture->width, data->ray->angle_rd, plane);
	pixel_array = (uint32_t *)texture->pixels;
	y_pixel_coordinate = (wall_top_pixel - (WINDOW_HEIGHT / 2)
			+ (data->ray->wall_h / 2)) * ((double)texture->height
			/ data->ray->wall_h);
	y_pixel_coordinate = fmax(0.0, fmin(y_pixel_coordinate, texture->height
				- 1));
	x_pixel_coordinate = fmax(0.0, fmin(x_pixel_coordinate, texture->width
				- 1));
	return (pixel_array[(int)y_pixel_coordinate * texture->width
			+ (int)x_pixel_coordinate]);
}

void	render_wall_background(t_data *data)
{
	int				rendered_pixel;
	int 			i;
	uint32_t		color;
	mlx_texture_t	*texture;
	
	i = 0;
	texture = data->ray->current_texture;
	rendered_pixel = data->ray->wall_top_pixel;
	while (++i < rendered_pixel)
		render_pixel(data, i, data->map->c_color); 
	while (rendered_pixel < data->ray->wall_top_pixel)
	{
		color = pixel_color(texture, data, rendered_pixel);
		color = reverse_bytes(color);
		if (color != 0)
			render_pixel(data, rendered_pixel, color);
		rendered_pixel++;
	}
	i = data->ray->wall_top_pixel;
	while ( ++i < WINDOW_HEIGHT)
		render_pixel(data, i, data->map->f_color);
}
