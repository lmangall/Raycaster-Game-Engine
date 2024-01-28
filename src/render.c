
#include "../include/cub3d.h"

int	get_color(t_data *data,
				int collision_orientation) // get the color of the wall
{
	data->ray->angle_rd = nor_angle(data->ray->angle_rd); // normalize the angle
	if (collision_orientation == VERTICAL)
	{
		if (data->ray->angle_rd > M_PI / 2 && data->ray->angle_rd < 3 * (M_PI
				/ 2))
			return (0xB5B5B5FF); // west wall
		else
			return (0xB5B5B5FF); // east wall
	}
	else
	{
		if (data->ray->angle_rd > 0 && data->ray->angle_rd < M_PI)
			return (0xF5F5F5FF); // south wall
		else
			return (0xF5F5F5FF); // north wall
	}
}

void	my_mlx_pixel_put(t_data *data, int y, int color)
{
	if (y < 0)
		return ;
	else if (y >= WINDOW_HEIGHT)
		return ;
	mlx_put_pixel(data->img, data->ray->screen_x, y, color);
}

float	nor_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

void	render_floor_ceiling(t_data *data)
{
	int	i;

	i = data->ray->b_pix;
	while (i < WINDOW_HEIGHT)
		my_mlx_pixel_put(data, i++, 0xB99470FF); // floor
	i = 0;
	while (i < data->ray->t_pix)
		my_mlx_pixel_put(data, i++, 0x89CFF3FF); // ceiling
}

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

uint32_t	pixel_color(mlx_texture_t *texture, t_data *data, int t_pix)
{
	double		x_pixel_coordinate;
	double		y_pixel_coordinate;
	double		factor;
	uint32_t	*pixel_array;
	uint32_t	color;

	if (data->ray->is_wall)
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

static mlx_texture_t	*texture_selection(t_data *data)
{
	data->ray->angle_rd = nor_angle(data->ray->angle_rd);
	if (data->ray->is_wall)
	{
		if (data->ray->angle_rd > M_PI / 2 && data->ray->angle_rd < 3 * (M_PI
				/ 2))
			return (data->textures->east);
		else
			return (data->textures->west);
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
	// data->ray->current_texture = data->textures->north;//change this depending on orientation
	data->ray->current_texture = texture_selection(data);
	data->ray->wall_h = wall_h;
	data->ray->t_pix = t_pix;
	data->ray->b_pix = b_pix;
}
