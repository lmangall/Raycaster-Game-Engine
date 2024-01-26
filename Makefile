
NAME	= cub3D
LIB_FT	= lib/libft
LIB_FT_A= lib/libft/libft.a

MLX = lib/MLX42/build/libmlx42.a
FLAG_MLX = -framework Cocoa -framework OpenGL -framework IOKit -lglfw
INCLUDE = -I/usr/local/Cellar/glfw/3.3.9/include/GLFW
LIB = -L/usr/local/Cellar/glfw/3.3.9/lib

CC		= cc
CFLAGS	= -Wall -Werror -Wextra -O3 -ffast-math #-fsanitize=address -g

MOBJS	= ${SRCS:%.c=%.o}
SRCS	= main.c \
			parser.c

all: $(NAME)

$(NAME): $(MOBJS)
	@make -s -C $(LIB_FT)
	@$(CC) $(CFLAGS) $(FLAG_MLX) $(MOBJS) $(LIB_FT_A) $(MLX) $(LIB) -o $(NAME)

%.o: %.c cub3d.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@make clean -s -C $(LIB_FT)
	@rm -f $(MOBJS)

mini:
	cc -O3 -ffast-math -framework Cocoa -framework OpenGL -framework IOKit -lglfw $(MLX) $(LIB) mini_cub3D.c -o mini_cub3D

fclean: clean
	@make fclean -s -C $(LIB_FT)
	@rm -f $(NAME)
	@rm -f $(NAME_B)
	@rm -f mini_cub3D

re: fclean all