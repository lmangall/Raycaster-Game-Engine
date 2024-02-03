
#include "../include/cub3d.h"

static void render_background_pixel(mlx_image_t *img, int top_color, int bottom_color)
{
    int x;
    int y;

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

void render_background(mlx_t *mlx)
{
    mlx_image_t *image;
    int top_color = 0x336699FF;    // Top color
    int bottom_color = 0xB99470FF; // Bottom color

    image = mlx_new_image(mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    render_background_pixel(image, top_color, bottom_color);
    mlx_image_to_window(mlx, image, 0, 0);
}