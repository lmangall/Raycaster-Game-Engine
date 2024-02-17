#include "cub3d.h"

#define RGBA(r, g, b, a) ((r << 24) | (g << 16) | (b << 8) | a)

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	minimap_init(t_data *data)
{
	data->minimap->height = 150;
	data->minimap->width = 300;
	data->minimap->offset_x = 20;
	data->minimap->offset_y = 20;
	data->minimap->scale_x = (double)data->minimap->width
		/ ((double)data->map->width * TILE_SIZE);
	data->minimap->scale_y = (double)data->minimap->height
		/ ((double)data->map->height * TILE_SIZE);
	data->minimap->player_position_x = (int)(data->player->x_pos_px
			* data->minimap->scale_x);
	data->minimap->player_position_y = (int)(data->player->y_pos_px
			* data->minimap->scale_y);
}

void	minimap_render_background(t_data *data)
{
	int	x;
	int	y;
	int	minimap_background_color;

	x = 0;
	y = 0;
	minimap_background_color = RGBA(0, 0, 0, 255);
	while (y < data->minimap->height)
	{
		x = 0;
		while (x < data->minimap->width)
		{
			if (render_pixel(data->img, x, y, minimap_background_color) == NULL)
				free_exit(data);
			x++;
		}
		y++;
	}
}

void	minimap_render_block(int offset_x, int offset_y, t_data *data)
{
	int		x_px;
	int		y_px;
	int		block_width_px;
	int		block_height_px;
	double	block_width_px_f;
	double	block_height_px_f;
	int		block_color;
	int		offset_x_px;
	int		offset_y_px;

	// Consider here also the evenutally padding of the minimap
	offset_x_px = offset_x * TILE_SIZE * data->minimap->scale_x;
	offset_y_px = offset_y * TILE_SIZE * data->minimap->scale_y;
	y_px = 0;
	block_width_px_f = data->minimap->scale_x * TILE_SIZE;
	block_height_px_f = data->minimap->scale_y * TILE_SIZE;
	block_width_px = ft_max((int)block_width_px_f, 1);
	block_height_px = ft_max((int)block_height_px_f, 1);
	block_color = RGBA(255, 255, 255, 255);
	while (y_px < block_height_px)
	{
		x_px = 0;
		while (x_px < block_width_px)
		{
			if (x_px + offset_x_px >= data->minimap->width || y_px
				+ offset_y_px >= data->minimap->height)
				break ;
			if (render_pixel(data->img, x_px + offset_x_px, y_px + offset_y_px,
					block_color) == NULL)
				free_exit(data);
			x_px++;
		}
		y_px++;
	}
}

void	minimap_render_walls(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			if (data->map->grid[y][x] == '1')
				minimap_render_block(x, y, data);
			x++;
		}
		y++;
	}
}

void	minimap_render_player(t_data *data)
{
	int	player_pos_x;
	int	player_pos_y;
	int	player_color;
	int	x;
	int	y;
	int	half_size;

	half_size = 3;
	player_pos_x = (int)(data->player->x_pos_px * data->minimap->scale_x);
	player_pos_y = (int)(data->player->y_pos_px * data->minimap->scale_y);
	player_color = RGBA(255, 0, 0, 255);
	y = player_pos_y - half_size;
	while (y <= player_pos_y + half_size)
	{
		x = player_pos_x - half_size;
		while (x <= player_pos_x + half_size)
		{
			if (x >= 0 && x < data->minimap->width && y >= 0
				&& y < data->minimap->height)
			{
				if (render_pixel(data->img, x, y, player_color) == NULL)
					free_exit(data);
			}
			x++;
		}
		y++;
	}
}

void	minimap_render_ray(t_data *data)
{
	int		ray_length;
	int		ray_color;
	double	scale_x;
	double	scale_y;
	int		player_pos_x;
	int		player_pos_y;
	int		dx;
	int		x;
	int		y;

	ray_length = 50;
	ray_color = RGBA(0, 255, 0, 255);
	scale_x = (double)data->minimap->width / ((double)data->map->width
			* TILE_SIZE);
	scale_y = (double)data->minimap->height / ((double)data->map->height
			* TILE_SIZE);
	player_pos_x = (int)(data->player->x_pos_px * scale_x);
	player_pos_y = (int)(data->player->y_pos_px * scale_y);
	dx = 0;
	while (dx <= ray_length)
	{
		x = player_pos_x + (int)(dx * cos(data->player->orientation_angle_rd));
		y = player_pos_y + (int)(dx * sin(data->player->orientation_angle_rd));
		if (x >= 0 && x < data->minimap->width && y >= 0
			&& y < data->minimap->height)
		{
			data->ray->screen_x = x;
			render_pixel(data->img, x, y, ray_color);
		}
		dx++;
	}
}

void	render_minimap(void *tmp)
{
	t_data *data;

	data = (t_data *)tmp;
	minimap_init(data);
	minimap_render_background(data);
	minimap_render_walls(data);
	minimap_render_player(data);
	minimap_render_ray(data);
}