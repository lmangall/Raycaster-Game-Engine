#include "cub3d.h"

#define RGBA(r, g, b, a) ((r << 24) | (g << 16) | (b << 8) | a)

static void init_minimap(t_data *data)
{
	data->minimap->height = 150;
	data->minimap->width = 300;
	data->minimap->offset_x = 20;
	data->minimap->offset_y = 20;
	// data->minimap->player_position_x = (int)(data->player->x_pos_px / TILE_SIZE);
	// data->minimap->player_position_y = (int)(data->player->y_pos_px / TILE_SIZE);
}

static void draw_background(t_data *data)
{
	int i = 0;
	int j = 0;
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

static void draw_walls(t_data *data)
{
	double scale_x = (double)data->minimap->width / data->map->width;
	double scale_y = (double)data->minimap->height / data->map->height;
	int color = RGBA(255, 255, 255, 255); // White color for walls

	int i = 0;
	while (i < data->map->width)
	{
		int j = 0;
		while (j < data->map->height)
		{
			if (data->map->grid[j][i] == '1') // Assuming '1' represents a wall
			{
				int x = (int)(i * scale_x);
				int y = (int)(j * scale_y);
				data->ray->screen_x = x;
				render_pixel(data, y, color);
			}
			j++;
		}
		i++;
	}
}

static void draw_player(t_data *data)
{
	int half_size = 3; // Half the size of the square to make it centered on the player
	double scale_x = (double)data->minimap->width / ((double)data->map->width * TILE_SIZE);
	double scale_y = (double)data->minimap->height / ((double)data->map->height * TILE_SIZE);
	int player_pos_x = (int)(data->player->x_pos_px * scale_x);
	int player_pos_y = (int)(data->player->y_pos_px * scale_y);
	int color = RGBA(255, 0, 0, 255);

	render_pixel(data, player_pos_y - half_size, color);
	render_pixel(data, player_pos_y + half_size, color);
	render_pixel(data, player_pos_y, color);
	render_pixel(data, player_pos_y, color);

	int dx = -half_size;
	int dy;

	while (dx <= half_size)
	{
		dy = -half_size;
		while (dy <= half_size)
		{
			int x = player_pos_x + dx;
			int y = player_pos_y + dy;
			if (x >= 0 && x < data->minimap->width && y >= 0 && y < data->minimap->height)
			{
				data->ray->screen_x = x;
				render_pixel(data, y, color);
			}
			dy++;
		}
		dx++;
	}
}

void render_minimap(void *tmp)
{
	t_data	*data;

	data = (t_data *)tmp;
	init_minimap(data);
	draw_background(data);
	draw_walls(data);
	draw_player(data);
}