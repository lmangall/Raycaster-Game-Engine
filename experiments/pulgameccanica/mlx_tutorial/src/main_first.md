We use three functions:

- mlx_init()
- mlx_new_window()
- mlx_loop()

We get two pointers here, one to the connector and one to the window.

```c
#include <mlx.h>

int main(void) {
  void *mlx_ptr;
  void *win_ptr;

  mlx_ptr = mlx_init();
  if (!mlx_ptr)
    return (1);
  win_ptr = mlx_new_window(mlx_ptr, 300, 300, "Hello World");
  if (!win_ptr)
    return (2);
  mlx_loop(mlx_ptr);
  return (0);
}
```

In the provided main function, we're using the MiniLibX library to create a simple graphical application. The process involves initializing the library and then creating a window. Let's break down the steps and the significance of the two pointers you mentioned:

1. **Initialization with `mlx_init()`:**

   - This function initializes the library and prepares it for use. It sets up the connection to the display (often referred to as the "display server" on systems using the X Window System or similar graphical systems).
   - The return value of `mlx_init()` is a pointer (`void *mlx_ptr`), commonly referred to as the "connection identifier" or "MLX instance". This pointer is crucial because it represents the established connection between your application and the graphical environment. You'll need this pointer for almost all subsequent calls to MiniLibX functions, as it tells the library which instance of the connection to the display server it should operate on.

2. **Window creation with `mlx_new_window()`:**

   - After initializing the library, you use `mlx_new_window()` to create a new window. This function requires the connection identifier we got from `mlx_init()`, dimensions for the window (width and height), and a title for the window.
   - The return value of `mlx_new_window()` is another pointer (`void *win_ptr`), which serves as the "window identifier". This pointer is essential for any operations specific to this window, such as drawing on it, setting its properties, or eventually destroying it. It essentially represents the window within the MiniLibX library and allows you to refer to this particular window in future function calls.

3. **Entering the event loop with `mlx_loop()`:**
   - The `mlx_loop()` function takes the connection identifier as its argument and enters the event loop. This loop keeps your application running, waiting for events (like key presses, mouse movements, or requests to redraw the window) and handling them as necessary. Without this loop, your program would terminate immediately after opening the window, giving you no chance to interact with it.

To explain more clearly, consider the analogy of opening a store (your application):

- **`mlx_init()`:** This is like opening the doors to the mall (the graphical display environment). The `mlx_ptr` you get back is akin to a keychain that gives you access to various facilities within the mall.
- **`mlx_new_window()`:** Now that you're in the mall, you open your store (create a window). The `win_ptr` is like the specific key to your store's front door, distinguishing it from every other store (window) in the mall.
- **`mlx_loop()`:** Finally, you open the store for business and wait for customers (events). The mall's security (the event loop) notifies you of any activity related to your store, so you can respond accordingly.

In this analogy, the "connection identifier" (`mlx_ptr`) and the "window identifier" (`win_ptr`) are distinct keys that serve different purposes: one for accessing the broader graphical environment and one for operating your specific "store" (window) within it.
