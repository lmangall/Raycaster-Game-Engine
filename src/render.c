
#include "../include/cub3d.h"
#include "MLX42.h"

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

uint32_t	pixel_color(mlx_texture_t *texture, t_data *data, int higher_pixel)
{
	uint32_t	*pixel_array;
	uint32_t	color;
	char		plane;

	double x_pixel_coordinate, y_pixel_coordinate, factor;
	plane = (data->ray->wall_collision_orientation == HORIZONTAL) ? 'x' : 'y';
	x_pixel_coordinate = adjust_mirroring(fmod((plane == 'x' ? data->ray->horizontal_x : data->ray->vertical_y)
				* (texture->width / TILE_SIZE), texture->width), texture->width,
			data->ray->angle_rd, plane);
	pixel_array = (uint32_t *)texture->pixels;
	factor = (double)texture->height / data->ray->wall_h;
	y_pixel_coordinate = (higher_pixel - (WINDOW_HEIGHT / 2)
			+ (data->ray->wall_h / 2)) * factor;
	if (y_pixel_coordinate < 0 || y_pixel_coordinate >= texture->height)
		return (0);
	x_pixel_coordinate = fmax(0.0, fmin(x_pixel_coordinate, texture->width
				- 1));
	color = pixel_array[(int)y_pixel_coordinate * texture->width
		+ (int)x_pixel_coordinate];
	color = reverse_bytes(color);
	return (color);
}

void	render_wall(t_data *data)
{
	int				higher_pixel;
	uint32_t		color;
	mlx_texture_t	*texture;

	texture = data->ray->current_texture;
	higher_pixel = data->ray->higher_pixel;
	while (higher_pixel < data->ray->lower_pixel)
	{
		color = pixel_color(texture, data, higher_pixel);
		if (color != 0)
		// Only render if color is not 0 (outside texture bounds)
		{
			render_pixel(data, higher_pixel, color);
		}
		higher_pixel++;
	}
}

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

void	init_ray(t_data *data)
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
