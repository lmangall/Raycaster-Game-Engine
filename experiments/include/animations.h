#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "../../MLX42/include/MLX42/MLX42.h"
#include "../../lib/libft/include/libft.h"
#include <stdio.h>

typedef struct s_rect {
  unsigned short int x;
  unsigned short int y;
  unsigned short int size_w;
  unsigned short int size_h;
  int color;
} t_rect;

typedef struct s_circle {
  unsigned short int x;
  unsigned short int y;
  unsigned short int radius;
  int color;
} t_circle;
void draw_rect(t_rect rect, mlx_image_t *img);
void draw_circle(t_circle circle, mlx_image_t *img);

#endif // ANIMATIONS_H