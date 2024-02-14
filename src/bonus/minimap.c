#include "cub3d.h"

#define RGBA(r, g, b, a) ((r << 24) | (g << 16) | (b << 8) | a)

static int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static void	init_minimap(t_data *data)
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

static void	render_background(t_data *data)
{
	int	x;
	int	y;
	int	minimap_background_color;

	// printf("render background\n");
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

// Why we need ft_max: see Note 1

static void	render_block(int offset_x, int offset_y, t_data *data)
{
	int		x;
	int		y;
	int		block_width_px;
	int		block_height_px;
	double	block_width_px_f;
	double	block_height_px_f;
	int		block_color;
	int		offset_x_px;
	int		offset_y_px;

	offset_x_px = offset_x * TILE_SIZE;
	offset_y_px = offset_y * TILE_SIZE;
	// printf("render block\n");
	y = 0;
	// Add +1 to include the last pixel and compensate for rounding down
	// when converting scales to integers.
	// block_width = (int)data->minimap->scale_x + 1;
	block_width_px_f = data->minimap->scale_x * TILE_SIZE;
	block_height_px_f = data->minimap->scale_y * TILE_SIZE;
	block_width_px = ft_max(block_width_px_f, 1);
	block_height_px = ft_max(block_height_px_f, 1);
	block_color = RGBA(255, 255, 255, 255);
	// printf("scale_x: %f, scale_y: %f\n", data->minimap->scale_x,
	// data->minimap->scale_y);
	// printf("block_width: %d\n", block_width_px);
	// printf("block_height: %d\n", block_height_px);
	while (y < block_height_px)
	{
		x = 0;
		while (x < block_width_px)
		{
			if (x + offset_x_px >= data->minimap->width || y
				+ offset_y_px >= data->minimap->height)
			{
				printf("x + offset_x_px: %d, y + offset_y_px: %d\n", x
					+ offset_x_px, y + offset_y_px);
				printf("break\n");
				break ;
			}
			// if (render_pixel(data->img, x + offset_x, y + offset_y,
			// block_color) == NULL)
			if (render_pixel(data->img, x + offset_x_px, y + offset_y_px,
					block_color) == NULL)
				free_exit(data);
			x++;
		}
		y++;
	}
}
// offset_x and offset_y are values in tiles, not pixels
// but they should be converted to pixels to render the block
// map->width and map->height are in tiles
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

	// printf("render player\n");
	half_size = 3;
	// printf("minimap->width: %d, minimap->height: %d\n", data->minimap->width,
	// 	data->minimap->height);
	// printf("map->width: %d, map->height: %d\n", data->map->width,
	// 	data->map->height);
	// printf("player->x_pos_px: %d, player->y_pos_px: %d\n",
	// 	data->player->x_pos_px, data->player->y_pos_px);
	// printf("minimap->scale_x: %f, minimap->scale_y: %f\n",
	// 	data->minimap->scale_x, data->minimap->scale_y);
	player_pos_x = (int)(data->player->x_pos_px * data->minimap->scale_x);
	player_pos_y = (int)(data->player->y_pos_px * data->minimap->scale_y);
	// printf("player_pos_x: %d, player_pos_y: %d\n", player_pos_x,
	// player_pos_y);
	player_color = RGBA(255, 0, 0, 255);
	y = player_pos_y - half_size;
	while (y <= player_pos_y + half_size)
	{
		x = player_pos_x - half_size;
		while (x <= player_pos_x + half_size)
		{
			if ((x < 0 || x >= data->minimap->width || y < 0))
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

	// printf("render ray\n");
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
	t_data	*data;

	data = (t_data *)tmp;
	init_minimap(data);
	render_background(data);
	render_walls(data);
	render_player(data);
	render_ray(data);
}

// Note 1
/*

The reason for using ft_max in calculating block_width and block_height is to ensure that every element we attempt to draw on the minimap has a visible representation. When scaling down from the game world to the minimap,
	the calculated dimensions for smaller elements might round down to zero due to the scale factor. Using ft_max guarantees that each element occupies at least one pixel on the minimap,
	making sure it's visibly represented even if it's significantly smaller than the scale might suggest.

*/