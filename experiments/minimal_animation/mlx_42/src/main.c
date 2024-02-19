#include "minimal_animation.h"

#define WIDTH 300
#define HEIGHT 300

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct padding {
  uint32_t top;
  uint32_t bottom;
  uint32_t left;
  uint32_t right;
  uint32_t horizontal;
  uint32_t vertical;
} padding_t;

typedef struct sizes {
  padding_t pad;
  uint32_t frame_width;
  uint32_t frame_height;
} sizes_t;

typedef struct mlx_frames {
  mlx_image_t **array;
  uint32_t num_frames;
  sizes_t sizes;
} mlx_frames_t;

void free_frames(mlx_frames_t *frames, uint32_t i, mlx_t *mlx) {
  while (i > 0) {
    mlx_delete_image(mlx, frames->array[i - 1]);
    i--;
  }
  free(frames->array);
  free(frames);
}

mlx_frames_t *extract_frames(const mlx_texture_t *texture, const sizes_t sizes,
                             mlx_frames_t *frames, uint32_t start_frame,
                             mlx_t *mlx) {
  uint32_t frames_across;
  uint32_t frames_down;
  uint32_t current_frame;
  uint32_t frame_x;
  uint32_t frame_y;
  uint32_t pixel_x;
  uint32_t pixel_y;
  uint8_t *src;
  uint8_t *dest;
  uint32_t i;
  uint32_t y;

  (void)frames_down;

  // Calculate the number of frames across and down
  frames_across = (texture->width - sizes.pad.left - sizes.pad.right) /
                  (sizes.frame_width + sizes.pad.horizontal * 2);
  frames_down = (texture->height - sizes.pad.top - sizes.pad.bottom) /
                (sizes.frame_height + sizes.pad.vertical * 2);
  frames->array = malloc((frames->num_frames + 1) * sizeof(mlx_image_t *));
  if (!frames->array)
    return (NULL);
  frames->array[frames->num_frames] = NULL;
  i = 0;
  while (i < frames->num_frames) {
    current_frame = start_frame + i;
    frame_x = current_frame % frames_across;
    frame_y = current_frame / frames_across;
    pixel_x = sizes.pad.left +
              frame_x * (sizes.frame_width + (sizes.pad.horizontal * 2));
    pixel_y = sizes.pad.top +
              frame_y * (sizes.frame_height + (sizes.pad.vertical * 2));
    frames->array[i] =
        mlx_new_image(mlx, sizes.frame_width, sizes.frame_height);
    if (!frames->array[i]->pixels) {

      // Handle error, possibly free already allocated frames
      free_frames(frames, i, mlx);
      exit(1);
    }
    y = 0;
    while (y < sizes.frame_height) {
      src = texture->pixels + ((pixel_y + y) * texture->width + pixel_x) *
                                  texture->bytes_per_pixel;
      dest = frames->array[i]->pixels +
             (y * sizes.frame_width) * texture->bytes_per_pixel;
      memmove(dest, src, sizes.frame_width * texture->bytes_per_pixel);
      y++;
    }
    i++;
  }
  return (frames);
}

void init_padding(padding_t *pad) {
  pad->top = 0;
  pad->bottom = 0;
  pad->left = 0;
  pad->right = 0;
  pad->horizontal = 0;
  pad->vertical = 0;
}

void init_sizes(sizes_t *sizes) {
  init_padding(&sizes->pad);
  sizes->frame_width = 0;
  sizes->frame_height = 0;
}

void init_frames(mlx_frames_t *frames) {
  frames->array = NULL;
  frames->num_frames = 0;
  init_sizes(&frames->sizes);
}

int main(void) {
  mlx_t *mlx;
  mlx_texture_t *texture;
  mlx_image_t *image;
  mlx_frames_t *frames;
  uint32_t i = 0;

  //   uint8_t i = 0;
  mlx = mlx_init(WIDTH, HEIGHT, "Mort!", NULL);
  if (mlx == NULL) {
    printf("Error initializing mlx\n");
    return (1);
  }
  texture = mlx_load_png("assets/dino_sprites_mort.png");
  if (texture == NULL) {
    printf("Error loading texture\n");
    return (1);
  }
  printf("texture->width: %d\n", texture->width);
  printf("texture->height: %d\n", texture->height);
  printf("texture->bytes_per_pixel: %d\n", texture->bytes_per_pixel);
  printf("texture->pixels: %p\n", texture->pixels);
  printf("Number of uint8_t 'pixels': %d\n",
         texture->width * texture->height * texture->bytes_per_pixel);
  printf("Number of uint32_t 'pixels': %d\n",
         texture->width * texture->height * texture->bytes_per_pixel / 4);
  image = mlx_texture_to_image(mlx, texture);
  if (image == NULL) {
    printf("Error creating image\n");
    return (1);
  }
  frames = NULL;
  init_frames(frames);
  frames->num_frames = 15;
  frames->sizes.frame_height = 24;
  frames->sizes.frame_width = 24;
  frames = extract_frames(texture, frames->sizes, frames, 0, mlx);

  while (i < frames->num_frames) {
    int32_t y;

    y = 24 * (i + 1);
    mlx_image_to_window(mlx, frames->array[i], 0, y);
    i++;
  }

  mlx_image_to_window(mlx, image, 0, 0);
  //   printf("Hello, World!\n");
  //   ft_putstr_fd("Hello, World!\n", 1);
  mlx_loop(mlx);
  mlx_delete_image(mlx, image);
  mlx_delete_texture(texture);
  mlx_terminate(mlx);
  return (0);
}
