#include "cub3d.h"

#define RGBA(r, g, b, a) ((r << 24) | (g << 16) | (b << 8) | a)

typedef struct s_minimap
{
	int offset_x;
	int offset_y;
	int width;
	int height;
} t_minimap;

void minimap(t_data *data)
{
	// mlx_image_t *minimap;
	int minimap_height;
	int minimap_width;
	int minimap_offset_x;
	int minimap_offset_y;
	int i;
	int j;


 (void)minimap_offset_x;
 (void)minimap_offset_y;
 
	// minimap_height = WINDOW_HEIGHT / 5;
	// minimap_width = WINDOW_WIDTH / 5;
	minimap_height = 150;
	minimap_width = 300;
	minimap_offset_x = 20;
	minimap_offset_y = 20;
	i = 0;
	j = 0;
	// minimap_z_depth = 0;
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
	// mlx_image_to_window(data->mlx, data->minimap, minimap_offset_x, minimap_offset_y);
	// if (data->img && data->img->count > 0) {
	// 	printf("data->img->count > 0\n");
    //     // Ensure the minimap is always rendered above the main game view
    //     minimap_z_depth = data->img->instances[0].z + 100;
	// 	if (data->minimap->count > 0)
	// 	{
	// 		printf("data->minimap->count > 0\n");
    //     	mlx_set_instance_depth(&(data->minimap->instances[0]), minimap_z_depth);

	// 	}
    // }
	// print instance count of minimap
	// printf("instances of img: %zu\n", data->img->count);
	// printf("z-idx of img: %d\n", data->img->instances[0].z);
	// printf("instances of data->minimap: %zu\n", data->minimap->count);
	// printf("z-idx of data->minimap: %d\n", data->minimap->instances[0].z);
	// printf("instances of background: %zu\n", data->background->count);
	// printf("z-idx of background: %d\n", data->background->instances[0].z);
	// data->minimap = minimap;

}