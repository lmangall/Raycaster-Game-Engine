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



	// minimap_height = WINDOW_HEIGHT / 5;
	// minimap_width = WINDOW_WIDTH / 5;
	minimap_height = 150;
	minimap_width = 300;
	minimap_offset_x = 20;
	minimap_offset_y = 20;
	i = 0;
	j = 0;
	data->minimap = mlx_new_image(data->mlx, minimap_width, minimap_height);
	if (data->minimap == NULL)
	{
		printf("Error: minimap is NULL\n");
		return ;
	}
	while (j < minimap_height)
	{
		i = 0;
		while (i < minimap_width)
		{
			mlx_put_pixel(data->minimap, i, j, RGBA(255, 255, 255, 255));
			i++;
		}
		j++;
	}
	mlx_image_to_window(data->mlx, data->minimap, minimap_offset_x, minimap_offset_y);
	// print instance count of minimap
	// printf("instances of img: %zu\n", data->img->count);
	// printf("z-idx of img: %d\n", data->img->instances[0].z);
	// printf("instances of data->minimap: %zu\n", data->minimap->count);
	// printf("z-idx of data->minimap: %d\n", data->minimap->instances[0].z);
	// printf("instances of background: %zu\n", data->background->count);
	// printf("z-idx of background: %d\n", data->background->instances[0].z);
	// data->minimap = minimap;

}