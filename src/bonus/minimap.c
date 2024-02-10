#include "cub3d.h"

#define RGBA(r, g, b, a) ((r << 24) | (g << 16) | (b << 8) | a)

void minimap(t_data *data)
{
	int minimap_height;
	int minimap_width;
	int minimap_offset_x;
	int minimap_offset_y;
	int i;
	int j;

	mlx_image_t *minimap;


	minimap_height = WINDOW_HEIGHT / 5;
	minimap_width = WINDOW_WIDTH / 5;
	minimap_offset_x = 20;
	minimap_offset_y = 20;
	i = 0;
	j = 0;
	minimap = mlx_new_image(data->mlx, minimap_width, minimap_height);
	if (minimap == NULL)
	{
		// free_data
		return ;
	}
	while (j < minimap_height)
	{
		i = 0;
		while (i < minimap_width)
		{
			mlx_put_pixel(minimap, i, j, RGBA(0, 0, 0, 255));
			i++;
		}
		j++;
	}
	mlx_image_to_window(data->mlx, minimap, minimap_offset_x, minimap_offset_y);
	data->minimap = minimap;
	// minimap->instances[0].z = -1;

}