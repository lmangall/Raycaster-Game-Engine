#include "cub3d.h"

#define RGBA(r, g, b, a) ((r << 24) | (g << 16) | (b << 8) | a)

static void	init_minimap(t_data *data)
{
<<<<<<< HEAD
	data->minimap->height = 150;
	data->minimap->width = 300;
	data->minimap->offset_x = 20;
	data->minimap->offset_y = 20;
	data->minimap->scale_x = (double)data->minimap->width
		/ (double)data->map->width;
	data->minimap->scale_y = (double)data->minimap->height
		/ (double)data->map->height;
	data->minimap->player_position_x = (int)(data->player->x_pos_px
		* data->minimap->scale_x);
	data->minimap->player_position_y = (int)(data->player->y_pos_px
		* data->minimap->scale_y);
}

static void	draw_background(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->minimap->width)
	{
		data->ray->screen_x = i;
		j = 0;
		while (j < data->minimap->height)
		{
			render_pixel(data, j, 0x80000000);
			j++;
		}
		i++;
	}
}

static void	render_block(t_data *data, int x, int y)
{
	int	dx;
	int	block_width;
	int	block_height;
	int	dy;
	int	pixel_x;
	int	pixel_y;

	dx = 0;
	// int color = RGBA(255, 255, 255, 255);
	block_width = (int)data->minimap->scale_x + 1;
	block_height = (int)data->minimap->scale_y + 1;
	while (dx < block_width)
	{
		dy = 0;
		while (dy < block_height)
		{
			pixel_x = x + dx;
			pixel_y = y + dy;
			if (pixel_x < data->minimap->width
				&& pixel_y < data->minimap->height)
			{
				data->ray->screen_x = pixel_x;
				render_pixel(data, pixel_y, RGBA(255, 255, 255, 255));
			}
			dy++;
		}
		dx++;
	}
}

static void	render_walls(t_data *data)
{
	int	x;
	int	y;
	int	i;
	int	j;

	i = 0;
	while (i < data->map->width)
	{
		j = 0;
		while (j < data->map->height)
		{
			if (data->map->grid[j][i] == '1')
			{
				x = (int)(i * data->minimap->scale_x);
				y = (int)(j * data->minimap->scale_y);
				render_block(data, x, y);
			}
			j++;
		}
		i++;
	}
}

static void	draw_player(t_data *data)
{
	double	scale_x;
	double	scale_y;
	int		player_pos_x;
	int		player_pos_y;
	int		color;
	int		dx;
	int		dy;
	int		x;
	int		y;

	int half_size = 3;
		// Half the size of the square to make it centered on the player
	scale_x = (double)data->minimap->width / ((double)data->map->width
		* TILE_SIZE);
	scale_y = (double)data->minimap->height / ((double)data->map->height
		* TILE_SIZE);
	player_pos_x = (int)(data->player->x_pos_px * scale_x);
	player_pos_y = (int)(data->player->y_pos_px * scale_y);
	color = RGBA(255, 0, 0, 255);
	render_pixel(data, player_pos_y - half_size, color);
	render_pixel(data, player_pos_y + half_size, color);
	render_pixel(data, player_pos_y, color);
	render_pixel(data, player_pos_y, color);
	dx = -half_size;
	while (dx <= half_size)
	{
		dy = -half_size;
		while (dy <= half_size)
		{
			x = player_pos_x + dx;
			y = player_pos_y + dy;
			if (x >= 0 && x < data->minimap->width && y >= 0
				&& y < data->minimap->height)
			{
				data->ray->screen_x = x;
				render_pixel(data, y, color);
			}
			dy++;
		}
		dx++;
	}
}

static void	render_player_ray(t_data *data)
{
	int		ray_length;
	int		color;
	double	scale_x;
	double	scale_y;
	int		player_pos_x;
	int		player_pos_y;
	int		dx;
	int		x;
	int		y;

	ray_length = 50;
	color = RGBA(0, 255, 0, 255);
	// Calculate the player's position on the minimap
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
			render_pixel(data, y, color);
		}
		dx++;
	}
}

void	render_minimap(void *tmp)
{
	t_data *data;

	data = (t_data *)tmp;
	init_minimap(data);
	draw_background(data);
	render_walls(data);
	draw_player(data);
	render_player_ray(data);
}