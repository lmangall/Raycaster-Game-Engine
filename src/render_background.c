
#include "../include/cub3d.h"

static void	render_background_pixel(mlx_image_t *img, uint32_t top_color,
		uint32_t bottom_color)
{
	int	x;
	int	y;

	y = 0;
	while (y < WINDOW_HEIGHT / 2)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(img, x, y, top_color);
			x++;
		}
		y++;
	}
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(img, x, y, bottom_color);
			x++;
		}
		y++;
	}
}

static uint32_t rgba_to_int(t_rgba color)
{
	return (color.r << 24 | color.g << 16 | color.b << 8 | 255);
}

void	render_background(mlx_t *mlx, t_rgba c, t_rgba f)
{
	mlx_image_t	*image;
	uint32_t			int_top_color;
	uint32_t			int_bottom_color;


	(void)c;
	(void)f;
	// top_color = 0x336699FF;    // Top color
	// bottom_color = 0xB99470FF; // Bottom color
    t_rgba top_color = {0, 0, 150};    // Subtle Blue
    t_rgba bottom_color = {0, 100, 0}; // Subtle Green

	int_top_color = rgba_to_int(top_color);
	int_bottom_color = rgba_to_int(bottom_color);
	//
	// top_color = rgba_to_int(c);
	// top_color = reverse_bytes(top_color);
	// bottom_color = rgba_to_int(f);
	// bottom_color = reverse_bytes(bottom_color);
	//
	image = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	render_background_pixel(image, int_top_color, int_bottom_color);
	mlx_image_to_window(mlx, image, 0, 0);
}
