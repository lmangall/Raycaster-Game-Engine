"MLX42 is dependent on a few other libraries:"

-ldl -lglfw -lw -lpthread

-**ldl**: This flag links against the dl library, which stands for _dynamic linking loader_. This library provides routines to dynamically load libraries at runtime rather than at compile time. It's essential for applications that need to load shared libraries on the fly.

-**lglfw**: This flag links against the _GLFW library_. GLFW is a library specifically designed for creating windows with OpenGL contexts and managing input and events. It's used in graphics applications for window management and handling user input.

-**pthread**: This flag links against the _pthreads library_, which stands for POSIX threads. It allows the application to use multithreading capabilities, enabling it to run multiple threads of execution concurrently. This is useful for improving the performance of an application by utilizing multiple CPU cores.

-lm: This flag links against the math library (libm). It provides access to mathematical functions beyond the basic arithmetic operations, such as trigonometric functions, exponentials, logarithms, etc.

`-pthread vs -lpthread`

The -pthread option not only links the program with the pthread library, like `-pthread` but also configures the compiler to correctly support multithreading features by defining appropriate macros.
