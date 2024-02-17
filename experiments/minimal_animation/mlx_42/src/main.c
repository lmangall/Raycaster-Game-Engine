#include "minimal_animation.h"

#define WIDTH 300
#define HEIGHT 300

int main() {
  mlx_t *mlx;
  mlx_texture_t *texture;
  mlx_image_t *image;

  mlx = mlx_init(WIDTH, HEIGHT, "Mort!", NULL);
  if (mlx == NULL) {
    printf("Error initializing mlx\n");
    return 1;
  }
  texture = mlx_load_png("assets/dino_sprites_mort.png");
  if (texture == NULL) {
    printf("Error loading texture\n");
    return 1;
  }
  image = mlx_texture_to_image(mlx, texture);
  if (image == NULL) {
    printf("Error creating image\n");
    return 1;
  }

  mlx_image_to_window(mlx, image, 0, 0);

  //   printf("Hello, World!\n");
  //   ft_putstr_fd("Hello, World!\n", 1);
  mlx_loop(mlx);
  mlx_delete_image(mlx, image);
  mlx_delete_texture(texture);
  mlx_terminate(mlx);

  return 0;
}
