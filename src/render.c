
#include "../include/cub3d.h"
#include "MLX42.h"

static void	mlx_draw_pixel(uint8_t *pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

void	my_mlx_pixel_put(t_data *data, int y, int color)
{
	uint8_t	*pixelstart;

	if (y < 0)
		return ;
	else if (y >= WINDOW_HEIGHT)
		return ;
	pixelstart = &data->img->pixels[(y * WINDOW_WIDTH + data->ray->screen_x)
		* 4];
	mlx_draw_pixel(pixelstart, color);
}

float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

int	reverse_bytes(int c)
{
	int	byte0;
	int	byte1;
	int	byte2;
	int	byte3;

	byte0 = (c & 0xFF) << 24;
	byte1 = (c & 0xFF00) << 8;
	byte2 = (c >> 8) & 0xFF00;
	byte3 = (c >> 24) & 0xFF;
	return (byte0 + byte1 + byte2 + byte3);
}

//       pixel color and render_wall are combined into one function
// void	render_wall(t_data *data)
// {
// 	int				t_pix;
// 	uint32_t		color;
// 	mlx_texture_t	*texture;
// 	double			factor;
// 	double			y_pixel_coordinate;
// 	double			x_pixel_coordinate;
// 	uint32_t		*pixel_array;
// 	int				texel_color;

// 	t_pix = data->ray->t_pix;
// 	texture = data->ray->current_texture;
// 	factor = (double)texture->height / data->ray->wall_h;
// 	y_pixel_coordinate = (t_pix - (WINDOW_HEIGHT / 2) + (data->ray->wall_h / 2))
// 		* factor;
// 	if (data->ray->wall_collision_orientation == HORIZONTAL)
// 		x_pixel_coordinate = fmod((data->ray->horizontal_x * (texture->width
// 						/ TILE_SIZE)), texture->width);
// 	else
// 		x_pixel_coordinate = fmod((data->ray->vertical_y * (texture->width
// 						/ TILE_SIZE)), texture->width);
// 	pixel_array = (uint32_t *)texture->pixels;
// 	while (t_pix < data->ray->b_pix)
// 	{
// 		if (y_pixel_coordinate >= 0 && y_pixel_coordinate < texture->height)
// 		{
// 			texel_color = pixel_array[(int)y_pixel_coordinate * texture->width
// 				+ (int)x_pixel_coordinate];
// 			color = reverse_bytes(texel_color);
// 			my_mlx_pixel_put(data, t_pix, color);
// 		}
// 		y_pixel_coordinate += factor;
// 		t_pix++;
// 	}
// }

uint32_t	pixel_color(mlx_texture_t *texture, t_data *data, int t_pix)
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
	y_pixel_coordinate = (t_pix - (WINDOW_HEIGHT / 2) + (data->ray->wall_h / 2))
		* factor;
	if (y_pixel_coordinate < 0)
		y_pixel_coordinate = 0;
	color = pixel_array[(int)y_pixel_coordinate * texture->width
		+ (int)x_pixel_coordinate];
	color = reverse_bytes(color);
	return (color);
}

void	render_wall(t_data *data)
{
	int				t_pix;
	uint32_t		color;
	mlx_texture_t	*texture;

	texture = data->ray->current_texture;
	t_pix = data->ray->t_pix;
	while (t_pix < data->ray->b_pix)
	{
		color = pixel_color(texture, data, t_pix);
		my_mlx_pixel_put(data, t_pix, color);
		t_pix++;
	}
}

mlx_texture_t	*texture_selection(t_data *data)
{
	if (data->ray->is_wall)
	{
		if (data->ray->angle_rd > M_PI / 2 && data->ray->angle_rd < 3 * (M_PI
				/ 2))
			return (data->textures->west);
		else
			return (data->textures->east);
	}
	else
	{
		if (data->ray->angle_rd > 0 && data->ray->angle_rd < M_PI)
			return (data->textures->south);
		else
			return (data->textures->north);
	}
}

void	init_ray(t_data *data)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	data->ray->length *= cos(nor_angle(data->ray->angle_rd
				- data->player->orientation_angle_rd));   // fix the fisheye
	wall_h = (TILE_SIZE / data->ray->length) * ((WINDOW_WIDTH / 2)
			/ tan(data->player->fov_rd / 2)); // get the wall height
	b_pix = (WINDOW_HEIGHT / 2) + (wall_h / 2);
	t_pix = (WINDOW_HEIGHT / 2) - (wall_h / 2);
	if (b_pix > WINDOW_HEIGHT)
		b_pix = WINDOW_HEIGHT;
	if (t_pix < 0)
		t_pix = 0;
	data->ray->current_texture = texture_selection(data);
	data->ray->wall_h = wall_h;
	data->ray->t_pix = t_pix;
	data->ray->b_pix = b_pix;
}
