#include "cub3d.h"

#define RGBA(r, g, b, a) ((r << 24) | (g << 16) | (b << 8) | a)

static void	init_minimap(t_data *data)
{
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

static void	render_background(t_data *data)
{
	int	x;
	int	y;
	int	minimap_background_color;

	printf("render background\n");
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

static void	render_block(int offset_x, int offset_y, t_data *data)
{
	int	x;
	int	y;
	int	block_width;
	int	block_height;
	int	block_color;

	printf("render block\n");
	y = 0;
	// Add +1 to include the last pixel and compensate for rounding down
	// when converting scales to integers.
	block_width = (int)data->minimap->scale_x + 1;
	block_height = (int)data->minimap->scale_y + 1;
	block_color = RGBA(255, 255, 255, 255);
	while (y < block_height)
	{
		x = 0;
		while (x < block_width)
		{
			if (x + offset_x > data->minimap->width || y
				+ offset_y > data->minimap->height)
				break ;
			if (render_pixel(data->img, x + offset_x, y + offset_y,
					block_color) == NULL)
				free_exit(data);
			x++;
		}
		y++;
	}
}

static void	render_walls(t_data *data)
{
	int	offset_x;
	int	offset_y;
	int	y;
	int	x;

	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			if (data->map->grid[y][x] == '1')
			{
				offset_x = (int)(x * data->minimap->scale_x);
				offset_y = (int)(y * data->minimap->scale_y);
				render_block(offset_x, offset_y, data);
			}
			x++;
		}
		y++;
	}
}

static void	render_player(t_data *data)
{
	int	player_pos_x;
	int	player_pos_y;
	int	player_color;
	int	x;
	int	y;
	int	half_size;

	printf("render player\n");
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
			if (!(x < 0 || x >= data->minimap->width || y < 0))
				break ;
			if (render_pixel(data->img, x, y, player_color) == NULL)
				free_exit(data);
			x++;
		}
		y++;
	}
}

static void	render_ray(t_data *data)
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

	printf("render ray\n");
	ray_length = 50;
	ray_color = RGBA(0, 255, 0, 255);
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
			render_pixel(data->img, x, y, ray_color);
		}
		dx++;
	}
}

void	render_minimap(void *tmp)
{
	t_data *data;

	data = (t_data *)tmp;
	init_minimap(data);
	render_background(data);
	render_walls(data);
	render_player(data);
	render_ray(data);
}