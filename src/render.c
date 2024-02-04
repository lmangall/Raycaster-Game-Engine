
#include "../include/cub3d.h"
#include "MLX42.h"

//       pixel color and render_wall are combined into one function
// void	render_wall(t_data *data)
// {
// 	int				higher_pixel;
// 	uint32_t		color;
// 	mlx_texture_t	*texture;
// 	double			factor;
// 	double			y_pixel_coordinate;
// 	double			x_pixel_coordinate;
// 	uint32_t		*pixel_array;
// 	int				texel_color;

// 	higher_pixel= data->ray->higher_pixel;
// 	texture = data->ray->current_texture;
// 	factor = (double)texture->height / data->ray->wall_h;
// 	y_pixel_coordinate = (higher_pixel- (WINDOW_HEIGHT / 2) + (data->ray->wall_h
//			/ 2))
// 		* factor;
// 	if (data->ray->wall_collision_orientation == HORIZONTAL)
// 		x_pixel_coordinate = fmod((data->ray->horizontal_x * (texture->width
// 						/ TILE_SIZE)), texture->width);
// 	else
// 		x_pixel_coordinate = fmod((data->ray->vertical_y * (texture->width
// 						/ TILE_SIZE)), texture->width);
// 	pixel_array = (uint32_t *)texture->pixels;
// 	while (higher_pixel< data->ray->lower_pixel)
// 	{
// 		if (y_pixel_coordinate >= 0 && y_pixel_coordinate < texture->height)
// 		{
// 			texel_color = pixel_array[(int)y_pixel_coordinate * texture->width
// 				+ (int)x_pixel_coordinate];
// 			color = reverse_bytes(texel_color);
// 			render_pixel(data, higher_pixel, color);
// 		}
// 		y_pixel_coordinate += factor;
// 		higher_pixel++;
// 	}
// }

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
		render_pixel(data, higher_pixel, color);
		higher_pixel++;
	}
}

uint32_t	pixel_color(mlx_texture_t *texture, t_data *data, int higher_pixel)
{
	double		x_pixel_coordinate;
	double		y_pixel_coordinate;
	double		factor;
	uint32_t	*pixel_array;
	uint32_t	color;

	if (data->ray->wall_collision_orientation == HORIZONTAL)
		x_pixel_coordinate = (int)fmodf((data->ray->horizontal_x
					* (texture->width / TILE_SIZE)), texture->width);
	else
		x_pixel_coordinate = (int)fmodf((data->ray->vertical_y * (texture->width
						/ TILE_SIZE)), texture->width);
	pixel_array = (uint32_t *)texture->pixels;
	factor = (double)texture->height / data->ray->wall_h;
	y_pixel_coordinate = (higher_pixel - (WINDOW_HEIGHT / 2)
			+ (data->ray->wall_h / 2)) * factor;
	if (y_pixel_coordinate < 0)
		y_pixel_coordinate = 0;
	color = pixel_array[(int)y_pixel_coordinate * texture->width
		+ (int)x_pixel_coordinate];
	color = reverse_bytes(color);
	return (color);
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
