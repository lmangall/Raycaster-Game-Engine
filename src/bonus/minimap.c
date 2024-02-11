#include "cub3d.h"

#define RGBA(r, g, b, a) ((r << 24) | (g << 16) | (b << 8) | a)



void	render_minimap(t_data *data)
{


	int i;
	int j;
	// int minimap_z_depth;


	// minimap_height = WINDOW_HEIGHT / 5;
	// minimap_width = WINDOW_WIDTH / 5;
	data->minimap->height = 150;
	data->minimap->width = 300;
	data->minimap->offset_x = 20;
	data->minimap->offset_y = 20;
	i = 0;
	j = 0;
	// minimap_z_depth = 0;
	// data->minimap = mlx_new_image(data->mlx, minimap_width, minimap_height);
	// if (data->minimap == NULL)
	// {
	// 	printf("Error: minimap is NULL\n");
	// 	return ;
	// }
	while (j < data->minimap->height)
	{
		i = 0;
		while (i < data->minimap->width)
		{
			mlx_put_pixel(data->minimap->img, i, j, RGBA(0, 0, 0, 255));
			i++;
		}
		j++;
	}

	// mlx_image_to_window(data->mlx, data->minimap, minimap_offset_x,
	// minimap_offset_y);
	// if (data->img && data->img->count > 0)
	// {
	// 	printf("data->img->count > 0\n");
	// 	// Ensure the minimap is always rendered above the main game view
	// 	minimap_z_depth = data->img->instances[0].z + 10;
	// 	if (data->minimap->count > 0)
	// 	{
	// 		printf("data->minimap->count > 0\n");
	// 		mlx_set_instance_depth(&(data->minimap->instances[0]),
	// 			minimap_z_depth);
	// 	}
	// }
	// print instance count of minimap

	// data->minimap = minimap;
}