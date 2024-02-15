#include "utils.h"

/* To create a new image in MLX42 we use the mlx_new_image function

t_img	new_img(int w, int h, t_win window) {
  t_img image;

  image.win = window;
  image.img_ptr = mlx_new_image(window.mlx_ptr, w, h);
  image.addr = mlx_get_data_addr(image.img_ptr, &(image.bpp),
  &(image.line_len),
									&(image.endian));
  image.w = w;
  image.h = h;
  return (image);
}

*/

/*  To put a pixel in the image we use the forbidden the mlx_put_pixel function

void	put_pixel_img(t_img img, int x, int y, int color) {
  char *dst;

  if (x >= 0 && y >= 0 && x < img.w && y < img.h) {
	dst = img.addr + (y * img.line_len + x * (img.bpp / 8));
	*(unsigned int *)dst = color;
  }
}
*/

/* To import an image from a file MinLibX has two functions:
- mlx_xpm_file_to_image
- mlx_png_file_to_image

The second one has leaks: https://harm-smits.github.io/42docs/libs/minilibx/images.html.
Therefore people use the first one.

t_img	new_file_img(char * path, t_win window) {
	t_img image;

	image.win = window;
	image.img_ptr = mlx_xpm_file_to_image(window.mlx_ptr, path, &image.w,
		&image.h);
	if (!image.img_ptr)
		write(2, "File could not be read\n", 23);
	else
		image.addr = mlx_get_data_addr(image.img_ptr, &(image.bpp),
			&(image.line_len), &(image.endian));
	return (image);
}
*/