#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

#define ESC 53        // key escape
#define ENTER 36      // key "enter"
#define FOLLOW 3      // key "f"
#define COLOR 8       // key "c"
#define UP 126        // key "arrow up"
#define DOWN 125      // key "arrow down"
#define PENGUIN 35    // key "p"
#define RAND_COLOR 15 // key "r"

int size = 10;
int follow = 0;
int color = 0x00FF00;

typedef struct s_win {
  void *mlx_ptr;
  void *win_ptr;
  int height;
  int width;
} t_win;

t_win new_program(int w, int h, char *str) {
  void *mlx_ptr;

  mlx_ptr = mlx_init();
  return ((t_win){mlx_ptr, mlx_new_window(mlx_ptr, w, h, str), w, h});
}

typedef struct s_img {
  t_win win;
  void *img_ptr;
  char *addr;
  int h;
  int w;
  int bpp;
  int endian;
  int line_len;
} t_img;

typedef struct s_square {
  unsigned short int x;
  unsigned short int y;
  unsigned short int size;
  int color;
} t_square;

t_img new_img(int w, int h, t_win window) {
  t_img image;

  image.win = window;
  image.img_ptr = mlx_new_image(window.mlx_ptr, w, h);
  image.addr = mlx_get_data_addr(image.img_ptr, &(image.bpp), &(image.line_len),
                                 &(image.endian));
  image.w = w;
  image.h = h;
  return (image);
}

void put_pixel_img(t_img img, int x, int y, int color) {
  char *dst;

  if (x >= 0 && y >= 0 && x < img.w && y < img.h) {
    dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
    *(unsigned int *)dst = color;
  }
}

void draw_square(t_square square, t_img img) {
  unsigned short int i;
  unsigned short int j;

  i = 0;
  while (i < square.size && i + square.y < img.h) {
    j = 0;
    while (j < square.size && j + square.x < img.w) {
      put_pixel_img(img, j + square.x, i + square.y, square.color);
      j++;
    }
    i++;
  }
}

int exit_tutorial(t_win *window) {
  if (window)
    mlx_destroy_window(window->mlx_ptr, window->win_ptr);
  exit(0);
}

// Function to find out which int corresponds to the key pressed
int key_hook(int keycode, void *param) {
  (void)param; // Avoid unused parameter warning
  printf("Key pressed: %d\n", keycode);
  return (0);
}

int get_color() { return (rand() % 2147483647); }

int read_keys(int key_pressed, void *param) {
  t_img *img;

  img = (t_img *)param;
  if (key_pressed == ESC || !img)
    exit_tutorial(&img->win);
  else if (key_pressed == ENTER)
    draw_square((t_square){0, 0, img->w, 0xFFFFFF}, *img);
  else if (key_pressed == FOLLOW)
    follow = !follow;
  else if (key_pressed == COLOR)
    color = get_color();
  // else if (key_pressed == PENGUIN)
  //         penguin(*img);
  else
    return (-1);
  mlx_put_image_to_window(img->win.mlx_ptr, img->win.win_ptr, img->img_ptr, 0,
                          0);
  return (0);
}

int read_mouse(int button, int mouse_x, int mouse_y, void *param) {
  int x;
  int y;
  t_img *img;
  t_square square;

  //   printf("read_mouse\n");
  //   printf("Mouse clicked at: %d, %d\n", mouse_x, mouse_y);

  img = (t_img *)param;
  if (!img)
    return (-1);
  if (mouse_x < 0 || mouse_y < 0 || mouse_x > img->w || mouse_y > img->h)
    return (2);
  x = ((mouse_x % img->w) / size) * size;
  y = ((mouse_y % img->h) / size) * size;
  color = get_color();
  square = (t_square){x, y, size, color};
  printf("Drawing square at: %d, %d, size: %d, color: %x\n", x, y, size, color);
  printf("Button pressed: %d\n", button);
  printf("square: %d, %d, %d, %x\n", square.x, square.y, square.size,
         square.color);
  draw_square(square, *img);
  mlx_put_image_to_window(img->win.mlx_ptr, img->win.win_ptr, img->img_ptr, 0,
                          0);
  (void)button;
  return (0);
}

int touchpad_move_hook(int x, int y, void *param) {
  (void)param;
  printf("Mouse moved to: %d, %d\n", x, y);
  return (0);
}

int touchpad_scroll_hook(double xoffset, double yoffset, void *param) {
  (void)param;
  printf("Scrolled: %f, %f\n", xoffset, yoffset);
  return (0);
}

int touchpad_button_hook(int button, int x, int y, void *param) {
  // Cast the param to the appropriate type if needed
  // t_img *img = (t_img *)param;
  (void)param; // Avoid unused parameter warning

  printf("Button %d pressed at (%d, %d)\n", button, x, y);

  // Your custom logic here

  return (0);
}

int main(void) {
  t_win tutorial;
  t_img image;

  (void)image;

  tutorial = new_program(300, 300, "Tutorial");
  if (!tutorial.mlx_ptr || !tutorial.win_ptr)
    return (0);
  image = new_img(300, 300, tutorial);
  //   put_pixel_img(image, 150, 150, 0x00FFFFFF);
  {
    draw_square((t_square){0, 0, 300, 0x00FF00}, image);
    mlx_put_image_to_window(image.win.mlx_ptr, image.win.win_ptr, image.img_ptr,
                            0, 0);
  }
  mlx_key_hook(tutorial.win_ptr, key_hook, NULL);
  mlx_hook(tutorial.win_ptr, 2, 0, read_keys, &image);
  //   This is the original call to the mouse hook but it's not working
  //   mlx_mouse_hook(tutorial.win_ptr, read_mouse, &image);
  mlx_hook(tutorial.win_ptr, 4, 0, read_mouse, &image);
  //   mlx_hook(tutorial.win_ptr, 6, 0, touchpad_move_hook, &image);
  //   mlx_hook(tutorial.win_ptr, 4, 0, touchpad_scroll_hook, &image);
  //   mlx_hook(tutorial.win_ptr, 4, 0, touchpad_button_hook, &image);

  mlx_hook(tutorial.win_ptr, 17, 0, exit_tutorial, &tutorial);
  mlx_loop(tutorial.mlx_ptr);
  return (0);
}