# Second Step

## The t_win strucht and compound literals

In C, the use of compound literals introduces a convenient way to define and initialize unnamed objects directly within an expression. This feature, introduced in the C99 standard, allows for the creation of temporary objects of a specified type, providing immediate initialization with values.

Consider the definition of a structure `t_win`, designed to encapsulate information about a graphical window, including pointers to the window and its graphical context, as well as dimensions:

```c
typedef struct s_win {
  void *mlx_ptr;
  void *win_ptr;
  int height;
  int width;
} t_win;
```

To instantiate and initialize an object of this type, one could traditionally declare a variable and then assign values to its fields. However, compound literals allow for a more succinct approach. The syntax `(type_name){ initializer_list }` is employed to achieve this, where `type_name` is the type of the desired object and `initializer_list` provides initial values for its fields.

For instance, the `new_program` function demonstrates the practical application of a compound literal to efficiently create and return a `t_win` object:

```c
t_win new_program(int w, int h, char *str) {
  void *mlx_ptr;

  mlx_ptr = mlx_init();
  return ((t_win){mlx_ptr, mlx_new_window(mlx_ptr, w, h, str), w, h});
}
```

In this example, a compound literal of type `t_win` is created and returned. It initializes the structure's fields with values obtained at runtime, including a pointer to a newly initialized graphical context (`mlx_ptr`) and a new window (`mlx_new_window(mlx_ptr, w, h, str)`), alongside the specified width (`w`) and height (`h`). This approach eliminates the need for temporary variables or dynamic allocation for the return value, streamlining the process of working with structured data.

The inclusion of compound literals in C99 facilitates concise and readable code, particularly useful in scenarios requiring temporary objects or immediate initialization of structures and arrays.

The return statement you're asking about employs a feature of C known as a "compound literal." This feature allows you to create and initialize an anonymous (unnamed) object of a specified type directly in an expression. The syntax for a compound literal looks like this: `(type_name){ initializer_list }`. Here's a breakdown of how it's used in your return statement:

```c
return ((t_win){mlx_ptr, mlx_new_window(mlx_ptr, w, h, str), w, h});
```

- **`t_win`**: This specifies the type of the compound literal, which in this case is a struct of type `t_win`. This tells the compiler that the compound literal will be an instance of `t_win`.

- **`{mlx_ptr, mlx_new_window(mlx_ptr, w, h, str), w, h}`**: This is the initializer list for the compound literal. It initializes the fields of the `t_win` struct in the order they are declared in the struct definition. Specifically:
  - `mlx_ptr` initializes the `mlx_ptr` field of the `t_win` struct.
  - `mlx_new_window(mlx_ptr, w, h, str)` calls the `mlx_new_window` function with the previously obtained `mlx_ptr`, along with the width (`w`), height (`h`), and title string (`str`) parameters. The return value (a pointer to the newly created window) initializes the `win_ptr` field of the `t_win` struct.
  - `w` initializes the `width` field of the `t_win` struct.
  - `h` initializes the `height` field of the `t_win` struct.

By using a compound literal in the return statement, the function `new_program` can efficiently create and return an instance of `t_win` without needing to allocate it dynamically or use a temporary variable. This technique is useful for returning struct instances from functions in a concise and readable manner.

It's worth noting that compound literals are a feature introduced in C99. Therefore, to use this syntax, your compiler needs to support C99 or later standards.

## The t_img structure

```c
typedef struct s_img
{
	t_win	win;
	void	*img_ptr;
	char	*addr;
	int		h;
	int		w;
	int		bpp;
	int		endian;
	int		line_len;
}		t_img;
```

**endian** int endian; - The endianess of the pixel data. In this context, it specifies how the bytes that make up a single pixel's color value are ordered in memory. If the value is 0, the system is likely using little-endian format, where the least significant byte is stored first. If it's 1, the system is using big-endian format, where the most significant byte is stored first. Knowing the endianess is necessary when you're directly reading from or writing to addr to manipulate pixel colors, as you need to correctly interpret the byte order of the color values.
