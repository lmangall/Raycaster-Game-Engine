

#include "../../MLX42/include/MLX42/MLX42.h"
#include "../include/utils.h"
#include "animations.h"
#include <signal.h>

#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 300

int stop_serv = 0;

void sig_handler(int sig) {
  (void)sig;
  stop_serv = 42;
  ft_putendl_fd("Signal recieved, for now... exit without free\n", 2);
  exit(1);
}

int main(void) {
  //   t_win tutorial;

  //   t_img image;
  mlx_t *tutorial;
  mlx_image_t *image;

  signal(SIGINT, sig_handler);
  //   tutorial = new_window(300, 300, "animations");
  //   if (!tutorial.win_ptr)
  // return (2);
  tutorial = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "animations", 0);
  if (!tutorial)
    return (2);
  //   image = new_img(300, 300, tutorial);
  image = mlx_new_image(tutorial, WINDOW_WIDTH, WINDOW_HEIGHT);

  {
    /* Put white pixel */
    // put_pixel_img(image, 150, 150, 0x00FFFFFF);
    mlx_put_pixel(image, 150, 150, 0x00FFFFFF);
    // mlx_put_image_to_window(image.win.mlx_ptr, image.win.win_ptr,
    // image.img_ptr, 0, 0);
    mlx_image_to_window(tutorial, image, 0, 0);
  }

  //   mlx_loop(tutorial.mlx_ptr);
  mlx_loop(tutorial);
  //   mlx_destroy_window(tutorial.mlx_ptr, tutorial.win_ptr);
  if (image)
    mlx_delete_image(tutorial, image);
  mlx_close_window(tutorial);
  if (tutorial)
    mlx_terminate(tutorial);
  exit(0);
}