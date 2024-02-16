# Experiments

## Resources

- Introduction to MinilibX in Intra https://elearning.intra.42.fr/notions/minilibx/subnotions

- MinilibX: Events

- MiniLibX 42 Docs https://harm-smits.github.io/42docs/libs/minilibx by (Harm Smits)[https://github.com/harm-smits]

- MiniLibX: Basic introduction, tutorials, tips & tricks https://gontjarow.github.io/MiniLibX/ by Gontjarow https://github.com/Gontjarow

## MiniLibX versions

The folder _minilibx_ containes the three repositories of the MiniLibX library:

- minilibx-linux
- minilibx_mms_20200219
- minilibx_opengl_20191021

The minilibx-linux is the principal repository. It containes 59 files in 5 directories.

The _mms_ version is tailored for macOS, providing Swift support for developers to easily integrate graphical functionalities into their Swift-based applications on macOS. The designation "mms" lacks a universally recognized meaning, unlike "opengl," which clearly indicates its reliance on the OpenGL graphics API. Along `.c` files there are a bunch of `.swift` files. Only 16 files in 3 directories.

The _opengl_ version leverage OpenGL, which is a cross platfrom API for rendering 2D and 3D graphics: basically it allows us to use the GPU to render the graphics. This version of MiniLibX will use X-Window for window managment and OpenGL to draw the graphics. 18 files in 1 directory. Like for the 'mms' version the opengl version has not only `.c` files but also `.m` files, which contain Objective-C code.

- [ ] What are these different files for?
- [ ] Which dependencies does MinLibX have?
- [ ] MinLibX, vs mlx vx MLX42: why do we find references to MinLibX as mlx?

## MiniLibX Functions (RTFM)

MiniLibX has 5 man pages:

- mlx (mlx_init)
- mlx_new_window (mlx_new_window, mlx_clear_window, mlx_destroy_window)
- mlx_new_image (mlx_new_image, mlx_get_data_addr, mlx_put_image_to_window, mlx_get_color_value, mlx_xpm_to_image, mlx_xpm_file_to_image, mlx_destroy_image)
- mlx_loop (mlx_loop. mlx_key_hook, mlx_mouse_hook, mlx_expose_hook, mlx_loop_hook)
- mlx_pixel_put

### General considerations

#### MiniLibX vs MLX42 functions signature

**MiniLibX** often uses `void* pointers` for arguments in its functions, such as `void *mlx_ptr`and`void *win_ptr`. This design choice provides a flexible interface that can accept a variety of pointer types, reflecting the library's C roots where strict type checking is less emphasized. Functions typically return an int to indicate success or failure, adhering to a common C pattern for error reporting.

**MLX42**, on the other hand, uses more specific types for its function arguments, like `mlx_t* mlx`. This approach enhances type safety, making the code more self-documenting and helping to catch type mismatches at compile time. By requiring specific pointer types, MLX42 can take full advantage of the compiler's type checking capabilities. Functions in MLX42 do not return a value but instead, rely on the state of the passed objects and internal error handling mechanisms to manage errors. This reflects a design choice that prioritizes clean API design and leverages modern C practices, including structured error handling.

### mlx

- _`mlx_init`_ is called without arguments, it creates the connection to the X-Server to link the 'display' and the program, in case of succeess, it returns a pointer to the connection identifier.

How does it compare to MLX42?

MLX42 has a similar function `mlx_t* mlx_init(int32_t width, int32_t height, const char* title, bool resize)`. The main difference is that MLX42's mlx_init creates also the new window: it means it is like MiniLibX's **mlx_init and mlx_new_window together**. MLX42's mlx_init creates the connection between the software and the display. It loads the OpenGL function pointers (MinLibX doesn't have this). It returns a `mlx_t*` which is a struct containing the current window instane.

## mlx_new_window

- _`mlx_new_window`_: `void *mlx_new_window (void *mlx_ptr, int size_x, int size_y, char *title);`
- _`mlx_clear_window`_: int mlx_clear_window ( void *mlx_ptr, void *win_ptr );
- _`mlx_destroy_window`_: int mlx_destroy_window ( void *mlx_ptr, void *win_ptr );

How does MLX42 relates to this?

As stated in /docs/42.md: "There is no window clearing function because students need to learn how to properly manage their images. They can still delete images and turn instances on or off, of course."

## mlx_new_image

## mlx_loop

- **`mlx_new_image`**: Creates a new image in memory.

  - Prototype: `void * mlx_new_image (void *mlx_ptr, int width, int height);`
  - Description: It returns a `void *` identifier needed to manipulate this image later. It only requires the size of the image to be created, using the `width` and `height` parameters, and the `mlx_ptr` connection identifier. The created image can be displayed on the screen using `mlx_put_image_to_window()`.

- **`mlx_get_data_addr`**: Returns information about the created image, allowing a user to modify it later.

  - Prototype: `char * mlx_get_data_addr (void *img_ptr, int *bits_per_pixel, int *size_line, int *endian);`
  - Description: It provides the address where the image is stored and information such as `bits_per_pixel`, `size_line`, and `endian`, facilitating direct image manipulation. This is like a getter function in C++. We could access the values of the data also directly but the idea is to not let the user to mess around with these data.

  ```c
  char	*mlx_get_data_addr(t_img *img,int *bits_per_pixel,
  			int *size_line,int *endian)
  {
  *bits_per_pixel = img->bpp;
  *size_line = img->size_line;
  *endian = img->image->byte_order;
  return (img->data);
  }
  ```

- **`mlx_put_image_to_window`**: Displays an image inside a specified window.

  - Prototype: `int mlx_put_image_to_window (void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y);`
  - Description: Requires three identifiers for the connection to the display, the window to use, and the image. The `(x, y)` coordinates define the placement of the image in the window.

- **`mlx_get_color_value`**: Translates an RGB color to a format understandable by the X-Server.

  - Prototype: `unsigned int mlx_get_color_value (void *mlx_ptr, int color);`
  - Description: Takes a standard RGB `color` parameter and returns an `unsigned int` value. The `bits_per_pixel` least significant bits of this value can be stored in the image, taking into account the endian difference. We don't need to care about this function, which just reduce the information in the 32 bits color of the input for the case that the BPP is lower than 24 bites.

- **`mlx_xpm_to_image`**: Creates a new image from XPM data.

  - Prototype: `void * mlx_xpm_to_image (void *mlx_ptr, char **xpm_data, int *width, int *height);`
  - Description: Fills a new image using the specified `xpm_data`. Handles transparency but may not support all types of XPM images.

- **`mlx_xpm_file_to_image`**: Creates a new image from an XPM file.

  - Prototype: `void * mlx_xpm_file_to_image (void *mlx_ptr, char *filename, int *width, int *height);`
  - Description: Similar to `mlx_xpm_to_image` but uses a file specified by `filename` to create the image.

- **`mlx_destroy_image`**: Destroys the given image.
  - Prototype: `int mlx_destroy_image (void *mlx_ptr, void *img_ptr);`
  - Description: Used to free the memory allocated for an image specified by `img_ptr`.

MLX42 equivalents:

- **mlx_new_image** and **mlx_destroy_image**: `mlx_new_image` for creating a new image buffer and `mlx_delete_image` for deleting an image and freeing its resources.
- **mlx_get_data_addr**: MLX42 doesn't have a direct equivalent that exposes pixel data through a function since OpenGL and GLFW handle image data differently. However, the mlx_image_t structure in MLX42 does contain a pixels pointer, which is somewhat analogous to accessing image data directly, but with a modern approach focusing on GPU-based rendering.
- **mlx_put_image_to_window**: `mlx_image_to_window` creates a new instance of an image, sharing the same pixel buffer, which is a way to render images to the window.
- **mlx_get_color_value**: There is no direct equivalent in MLX42 since OpenGL handles color through shaders and GPU-based operations, making manual color value adjustments unnecessary for most use cases.
- **mlx_xpm_to_image** and **mlx_xpm_file_to_image**: `mlx_load_xpm42` loads an XPM42 texture, which is a modernized approach to handling XPM files. Additionally, MLX42 supports PNG textures directly through `mlx_load_png`, reflecting its modern capabilities.

### mlx hook

- **`mlx_loop`**: Enters the program into an infinite loop to process events.

  - Prototype: `int mlx_loop (void *mlx_ptr);`
  - Description: This function is an infinite loop that waits for events from the window (like key presses or mouse clicks) and calls the appropriate callback functions associated with these events. It's essential for any graphical application that requires interaction.
  - **MLX42 Equivalent**: `void mlx_loop (mlx_t* mlx);`
    - In MLX42, `mlx_loop` also serves the purpose of entering an infinite event processing loop. The difference lies in the underlying system (GLFW) used for handling the events, which can provide a more modern and efficient event processing mechanism.

- **`mlx_key_hook`**: Sets a callback function for key press events on a specific window.

  - Prototype: `int mlx_key_hook (void *win_ptr, int (*funct_ptr)(), void *param);`
  - Description: Assigns a user-defined function to be called when a key press event occurs on the specified window. This allows for custom responses to keyboard input.
  - **MLX42 Equivalent**: `void mlx_key_hook (mlx_t* mlx, mlx_keyfunc func, void* param);`
    - MLX42 uses a similar concept for key events, allowing developers to define custom actions when keys are pressed. The callback function in MLX42, however, provides more detailed information about the key event through the `mlx_key_data_t` structure.

---

- **`mlx_mouse_hook`**: Sets a callback function for mouse click events on a specific window.

  - Prototype: `int mlx_mouse_hook (void *win_ptr, int (*funct_ptr)(), void *param);`
  - Description: Allows for a user-defined function to be called when a mouse button is pressed within the window's context. It's useful for interactive applications requiring mouse input.
  - **MLX42 Equivalent**: `void mlx_mouse_hook (mlx_t* mlx, mlx_mousefunc func, void* param);`
    - Similarly, MLX42 provides functionality to handle mouse button events. The callback in MLX42 can distinguish between different mouse buttons and actions (press, release) and includes modifier keys.

---

- **`mlx_expose_hook`**: Sets a callback function for redraw events on a specific window.

  - Prototype: `int mlx_expose_hook (void *win_ptr, int (*funct_ptr)(), void *param);`
  - Description: Configures a callback to handle expose events, which occur when a window part becomes visible and needs to be redrawn. This is crucial for updating the window's contents appropriately.
  - **MLX42 Relation**: No direct equivalent. Redrawing in MLX42 is typically handled within the main loop or through GLFW's window refresh callbacks, leveraging OpenGL's rendering capabilities to manage window content updates efficiently.

---

- **`mlx_loop_hook`**: Sets a callback function to be called repeatedly during the event loop when no other events are being processed.

  - Prototype: `int mlx_loop_hook (void *mlx_ptr, int (*funct_ptr)(), void *param);`
  - Description: This allows for continuous execution of a function, useful for animations or background tasks within the graphical application, without needing an external event trigger.
  - **MLX42 Equivalent**: `bool mlx_loop_hook (mlx_t* mlx, void (*f)(void*), void* param);`
    - MLX42 offers a similar functionality, enabling developers to execute custom code in the absence of other events. This feature is particularly useful for animations, game logic updates, or any continuous monitoring within the application.

---

These comparisons highlight the evolution of event handling from MiniLibX to MLX42, showcasing how MLX42 adapts and extends the foundational concepts of MiniLibX with a modern approach facilitated by GLFW and OpenGL.

## Pulgameccanica Tutorials

### Mlx starter pack

https://pulgamecanica.herokuapp.com/posts/mlx-starter-pack

### Mlx animations

## Glossary

### General

**MiniLibX**: simple X-Window (X11R6) programming API in C, designed for students, suitable for X-beginners. Mini refers to the fact that the library is an abstraction over the LibX library.

**LibX**:

**X-Window System**: A system the manages the graphical windows we interact with. X-Window is a Windowing system for Bitmap displays, mostly used in Unix-like systems. There are at least 20 different other windowing systems. On a Linux system we can run different concurrently windowing systems at the same time. https://en.wikipedia.org/wiki/X_Window_System

**OpenGL**: A cross platform API for rendering 2D and 3D graphics. OpenGL can work with different Windowing Systems besides the X-Window System. For example on MacOS it will use Cocoa.

**GLFW**: GLFW is an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan development on the desktop. It provides a simple API for creating windows, contexts and surfaces, receiving input and events. GLFW is written in C and supports Windows, macOS, X11 and Wayland. GLFW is the cross-platfrom part related to the Window System for OpenGL. OpenGL doesn't know how to manage windows. Each OS has its own Windowing System and GLFW abstracts all the different implementations for the different systems. https://www.glfw.org/

**Endianess**: Property of t_img in mlx_int.h in MiniLibX. It represents where the most significat byte is saved. You can write a 32-bit integer starting from left or starting from right.
**Stride of an array**: https://en.wikipedia.org/wiki/Stride_of_an_array. The image struct from mlx_int.h has a field line_len, which represents this value. A string representing an image could start with some sort of padding, so that width, length and BPP are not enought information to know when to skip to the next line.

### Extras

**Compound Literals**: Found in Pulgameccanica's Minilibx Tutorial: https://gcc.gnu.org/onlinedocs/gcc/Compound-Literals.html

### Trees

#### minilibx-linux

```

.
├── LICENSE
├── Makefile
├── Makefile.mk
├── README.md
├── configure
├── man
│ ├── man1
│ │ ├── mlx.1
│ │ ├── mlx_loop.1
│ │ ├── mlx_new_image.1
│ │ ├── mlx_new_window.1
│ │ └── mlx_pixel_put.1
│ └── man3
│ ├── mlx.3
│ ├── mlx_loop.3
│ ├── mlx_new_image.3
│ ├── mlx_new_window.3
│ └── mlx_pixel_put.3
├── mlx.h
├── mlx_clear_window.c
├── mlx_destroy_display.c
├── mlx_destroy_image.c
├── mlx_destroy_window.c
├── mlx_expose_hook.c
├── mlx_ext_randr.c
├── mlx_flush_event.c
├── mlx_get_color_value.c
├── mlx_get_data_addr.c
├── mlx_hook.c
├── mlx_init.c
├── mlx_int.h
├── mlx_int_anti_resize_win.c
├── mlx_int_do_nothing.c
├── mlx_int_get_visual.c
├── mlx_int_param_event.c
├── mlx_int_set_win_event_mask.c
├── mlx_int_str_to_wordtab.c
├── mlx_int_wait_first_expose.c
├── mlx_key_hook.c
├── mlx_lib_xpm.c
├── mlx_loop.c
├── mlx_loop_hook.c
├── mlx_mouse.c
├── mlx_mouse_hook.c
├── mlx_new_image.c
├── mlx_new_window.c
├── mlx_pixel_put.c
├── mlx_put_image_to_window.c
├── mlx_rgb.c
├── mlx_screen_size.c
├── mlx_set_font.c
├── mlx_string_put.c
├── mlx_xpm.c
├── mlx_xpm.c.ok
├── rgb2c.pl
└── test
├── Makefile.mk
├── main.c
├── new_win.c
├── open.xpm
├── open24.xpm
├── open30.xpm
└── run_tests.sh

5 directories, 59 files

```

#### minilibx_mms_20200219

```

.
├── Makefile
├── font.c
├── interface.swift
├── man
│ └── man3
│ ├── mlx.3
│ ├── mlx_loop.3
│ ├── mlx_new_image.3
│ ├── mlx_new_window.3
│ └── mlx_pixel_put.3
├── mlx.h
├── mlx_image.swift
├── mlx_init.swift
├── mlx_png.c
├── mlx_rgb.c
├── mlx_string_put.c
├── mlx_window.swift
└── mlx_xpm.c

3 directories, 16 files

```

#### minilibx_opengl_20190121

```

.
├── Makefile
├── font.c
├── font.xcf
├── mlx.h
├── mlx_init_loop.m
├── mlx_int.h
├── mlx_int_str_to_wordtab.c
├── mlx_mouse.m
├── mlx_new_image.m
├── mlx_new_window.h
├── mlx_new_window.m
├── mlx_opengl.h
├── mlx_opengl.m
├── mlx_png.c
├── mlx_png.h
├── mlx_rgb.c
├── mlx_shaders.c
└── mlx_xpm.c

1 directory, 18 files

```

```

```

```

```

### Other Resources

- Xlib: the real deal. This is the library of which MiniLibX is the reduction of: https://www.x.org/releases/current/doc/libX11/libX11/libX11.html
