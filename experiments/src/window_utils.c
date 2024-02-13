#include "../include/animations.h"
#include "utils.h"

// t_win new_window(int w, int h, char *str)
// {
// 	void	*mlx_ptr;

// 	mlx_ptr = mlx_init();
// 	return ((t_win) {mlx_ptr, mlx_new_window(mlx_ptr, w, h, str), w, h});
// }

t_win new_window(int width, int height, char *title) {
  mlx_t *mlx_ptr;
  t_win win;

  mlx_ptr = mlx_init(width, height, title, 0);

  if (!mlx_ptr) {
    fprintf(stderr, "Failed to initialize MLX42\n");
    exit(EXIT_FAILURE); // Exit or handle the error as appropriate
  }
  win.mlx_ptr = mlx_ptr;
  win.width = width;
  win.height = height;
  win.background = (t_rect){0, 0, width, height, 0x00a4ff32};
  return win;
}