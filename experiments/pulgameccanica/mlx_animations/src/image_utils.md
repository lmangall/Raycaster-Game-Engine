# Image Utils (MinLibX vs MLX42 vs Pulga)

## The struct for an image

- MinLibX: https://github.com/42Paris/minilibx-linux/blob/master/mlx_int.h#L85C1-L98C12

```c
typedef struct	s_img
{
	XImage			*image;
	Pixmap			pix;
	GC				gc;
	int				size_line;
	int				bpp;
	int				width;
	int				height;
	int				type;
	int				format;
	char			*data;
	XShmSegmentInfo	shm;
}				t_img;
```

- `XImage *image`: A pointer to an XImage structure, which represents an image in memory. XImage contains data about the pixel values of the image, its size, and its format, among other things. This structure is used by X11 to manipulate images in client applications.

- `Pixmap pix`: A Pixmap is an off-screen displayable pixel map in X11, used for drawing operations. It's similar to a bitmap but can have various depths. This field likely stores a handle to a pixmap that might be used for rendering the image onto the screen or another drawable.

- `GC gc`: A graphics context (GC) in X11 holds graphical state information, such as foreground and background colors, line drawing styles, etc. It's used when drawing on drawables like windows or pixmaps.

- `int size_line`: This field likely represents the size (in bytes) of a single line of the image. It's useful for calculations involving direct manipulation of the data field, such as iterating over rows of pixels.

- `int bpp`: Bits per pixel (bpp) indicates the color depth of the image. It tells you how many bits are used to represent each pixel, which affects the color range and the image's memory footprint.

- `int width`: The width of the image in pixels.
- `int height`: The height of the image in pixels.
- `int type`: This field could specify the type of image or possibly its source (e.g., whether it's created in memory or loaded from a file). The exact meaning might depend on the context in which t_img is used.
- `int format`: Specifies the pixel format of the image. This could indicate how pixel data is structured (e.g., RGB, RGBA, etc.) and how it should be interpreted.
- `char *data`: A pointer to the actual pixel data of the image. This buffer holds the image's pixels as specified by the format and bpp fields.
- `XShmSegmentInfo shm`: This is a structure used with the X11 Shared Memory Extension (MIT-SHM), which allows images to be shared between the X server and a client application without copying data, improving performance. It contains information necessary to manage shared memory, such as segment IDs and addresses.

- MLX:

```c
typedef struct mlx_image
{
	const uint32_t	width;
	const uint32_t	height;
	uint8_t*		pixels;
	mlx_instance_t*	instances;
	size_t			count;
	bool			enabled;
	void*			context;
}	mlx_image_t;
```

## Create a new image

- MinLibX: `mlx_new_image`
- MLX42: `mlx_new_img`
- create a new image in MLX42 we use the mlx_new_image function

```c
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
```

\*/

/\* To put a pixel in the image we use the forbidden the mlx_put_pixel function

void put_pixel_img(t_img img, int x, int y, int color) {
char \*dst;

if (x >= 0 && y >= 0 && x < img.w && y < img.h) {
dst = img.addr + (y _ img.line_len + x _ (img.bpp / 8));
_(unsigned int _)dst = color;
}
}
\*/

/\* To import an image from a file MinLibX has two functions:

- mlx_xpm_file_to_image
- mlx_png_file_to_image

The second one has leaks: https://harm-smits.github.io/42docs/libs/minilibx/images.html.
Therefore people use the first one.

t_img new_file_img(char \* path, t_win window) {
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
\*/
