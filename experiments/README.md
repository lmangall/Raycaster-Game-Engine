# Experiments

## MiniLibX

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

### Glossary

**MiniLibX**: simple X-Window (X11R6) programming API in C, designed for students, suitable for X-beginners.

**X-Window System**: A system the manages the graphical windows we interact with. X-Window is a Windowing system for Bitmap displays, mostly used in Unix-like systems. There are at least 20 different other windowing systems. On a Linux system we can run different concurrently windowing systems at the same time.

**OpenGL**: A cross platform API for rendering 2D and 3D graphics. OpenGL can work with different Windowing Systems. For example on MacOS it will use Cocoa.

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
│   ├── man1
│   │   ├── mlx.1
│   │   ├── mlx_loop.1
│   │   ├── mlx_new_image.1
│   │   ├── mlx_new_window.1
│   │   └── mlx_pixel_put.1
│   └── man3
│       ├── mlx.3
│       ├── mlx_loop.3
│       ├── mlx_new_image.3
│       ├── mlx_new_window.3
│       └── mlx_pixel_put.3
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
│   └── man3
│       ├── mlx.3
│       ├── mlx_loop.3
│       ├── mlx_new_image.3
│       ├── mlx_new_window.3
│       └── mlx_pixel_put.3
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
