#include "cub3d.h"

#define RGBA(r, g, b, a) ((r << 24) | (g << 16) | (b << 8) | a)

void	render_minimap(void *tmp)
{
	t_data *data;

	data = (t_data *)tmp;

	double scale_x;
	double scale_y;
	int player_pos_x;
	int player_pos_y;
	int dx;
	int dy;
	int x;
	int y;

	int i;
	int j;

	data->minimap->height = 150;
	data->minimap->width = 300;
	data->minimap->offset_x = 20;
	data->minimap->offset_y = 20;
	i = 0;
	j = 0;
	while (j < data->minimap->height)
	{
		i = 0;
		while (i < data->minimap->width)
		{
			mlx_put_pixel(data->img, i, j, RGBA(0, 0, 0, 255));
			i++;
		}
		j++;
	}
	// Calculate the scale of the minimap
	scale_x = (double)data->minimap->width / ((double)data->map->width
		* TILE_SIZE);
	scale_y = (double)data->minimap->height / ((double)data->map->height
		* TILE_SIZE);
	// Calculate the player position on the minimap
	player_pos_x = (int)data->player->x_pos_px * scale_x;
	player_pos_y = (int)data->player->y_pos_px * scale_y;

	// Draw the player on the minimap as small square
	int half_size = 3;
	// Half the size of the square to make it centered on the player

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
				mlx_put_pixel(data->img, x, y, RGBA(255, 0, 0, 255));
			}
			dy++;
		}
		dx++;
	}
}