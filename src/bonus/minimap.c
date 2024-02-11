#include "cub3d.h"

#define RGBA(r, g, b, a) ((r << 24) | (g << 16) | (b << 8) | a)

static void init_minimap(t_data *data)
{
	data->minimap->height = 150;
	data->minimap->width = 300;
	data->minimap->offset_x = 20;
	data->minimap->offset_y = 20;
}

static void draw_background(t_data *data)
{
	int i = 0;
	int j = 0;
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
}

static void draw_line(t_data *data, int x0, int y0, int x1, int y1, uint32_t color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        if (x0 >= 0 && x0 < data->minimap->width && y0 >= 0 && y0 < data->minimap->height)
        {
            mlx_put_pixel(data->img, x0, y0, color);
        }

        if (x0 == x1 && y0 == y1)
        {
            break;
        }

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}


static void draw_player(t_data *data, int player_pos_x, int player_pos_y)
{
	int half_size = 3; // Half the size of the square to make it centered on the player
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
				mlx_put_pixel(data->img, x, y, RGBA(255, 0, 0, 255));
			}
			dy++;
		}
		dx++;
	}

	// Draw the field of view
	int fov_left_x = player_pos_x + cos(data->player->orientation_angle_rd - data->player->fov_rd / 2) * data->minimap->width;
	int fov_left_y = player_pos_y + sin(data->player->orientation_angle_rd - data->player->fov_rd / 2) * data->minimap->height;
	int fov_right_x = player_pos_x + cos(data->player->orientation_angle_rd + data->player->fov_rd / 2) * data->minimap->width;
	int fov_right_y = player_pos_y + sin(data->player->orientation_angle_rd + data->player->fov_rd / 2) * data->minimap->height;

	draw_line(data, player_pos_x, player_pos_y, fov_left_x, fov_left_y, RGBA(0, 255, 0, 255));
	draw_line(data, player_pos_x, player_pos_y, fov_right_x, fov_right_y, RGBA(0, 255, 0, 255));
}

void render_minimap(void *tmp)
{
	t_data	*data;
	double scale_x;
	double scale_y;
	int player_pos_x;
	int player_pos_y;

	data = (t_data *)tmp;

	init_minimap(data);
	draw_background(data);

	// Calculate the scale of the minimap
	scale_x = (double)data->minimap->width / ((double)data->map->width * TILE_SIZE);
	scale_y = (double)data->minimap->height / ((double)data->map->height * TILE_SIZE);
	// Calculate the player position on the minimap
	player_pos_x = (int)data->player->x_pos_px  * scale_x;
	player_pos_y = (int)data->player->y_pos_px  * scale_y;

	draw_player(data, player_pos_x, player_pos_y);
}