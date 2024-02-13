#include "animations.h"

void draw_rect(t_rect rect, mlx_image_t *img) {
  unsigned short int i;
  unsigned short int j;

  i = 0;
  while (i < rect.size_h && i + rect.y < img->height) {
    j = 0;
    while (j < rect.size_w && j + rect.x < img->width) {
      mlx_put_pixel(img, j + rect.x, i + rect.y, rect.color);
      j++;
    }
    i++;
  }
}

// void draw_circle(t_circle circle, t_img img) {
void draw_circle(t_circle circle, mlx_image_t *img) {
  unsigned short int i;
  unsigned short int j;

  i = 0;
  while (i < circle.radius * 2 && i + circle.y < img->height) {
    j = 0;
    while (j < circle.radius * 2 && j + circle.x < img->width) {
      if (((j - circle.radius) * (j - circle.radius)) +
              ((i - circle.radius) * (i - circle.radius)) <
          (circle.radius * circle.radius)) {
        mlx_put_pixel(img, j + circle.x, i + circle.y, circle.color);
      }
      j++;
    }
    i++;
  }
}
