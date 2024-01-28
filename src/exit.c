
#include "../include/cub3d.h"

// static void free_textures(t_textures *textures)
// {
//     if (textures != NULL)
//     {
//         // Free individual texture paths
//         mlx_delete_texture(textures->north);
//         mlx_delete_texture(textures->south);
//         mlx_delete_texture(textures->west);
//         mlx_delete_texture(textures->east);
//         mlx_delete_texture(textures->floor);
//         mlx_delete_texture(textures->ceiling);

//         // Free the t_textures structure
//         free(textures);
//     }
// }

void ft_exit(t_data *data) // exit the game
{
  int i = 0;
  while (data->map->grid[i])
    free(data->map->grid[i++]); // free the map line by line
  free(data->map->grid);        // free the map
  free(data->map);              // free the data structure
  free(data->player);           // free the player structure
  free(data->ray);              // free the ray structure
  //  free_textures(data->textures); // free the textures
  mlx_delete_image(data->mlx, data->img); // delete the image
  mlx_close_window(data->mlx);            // close the window
  mlx_terminate(data->mlx);               // terminate the mlx pointer
  printf("Game closed\n");                // print the message
  exit(0);                                // exit the game
}