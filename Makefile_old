NAME = cub3d

CC = cc -g
CFLAGS = -Wall -Wextra -Werror
MLX42FLAGS = -ldl -lglfw -pthread -lm

LIBFT = ./lib/libft/libft.a
FT_PRINTF = ./lib/ft_printf/libftprintf.a
LIBMLX = ./lib/MLX42-master
MLX42 = ./lib/MLX42-master/build/libmlx42.a

INCLUDE = -I./include -I$(LIBMLX)/include -I./lib/libft/src

SRC_DIR = src
OBJ_DIR = obj

SOURCES = $(addprefix $(SRC_DIR)/, main.c)
OBJECTS = $(addprefix $(OBJ_DIR)/, $(notdir $(SOURCES:.c=.o)))

MLX_REPO = https://github.com/codam-coding-college/MLX42.git
MLX_DIR = lib/MLX42-master

all: $(LIBFT) $(FT_PRINTF) $(MLX42) $(NAME)

$(NAME): $(OBJECTS) $(LIBFT) $(MLX42) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(OBJECTS) -L./lib/libft -lft $(MLX42) $(MLX42FLAGS) $(FT_PRINTF) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT):
	$(MAKE) -C ./lib/libft

$(FT_PRINTF):
	$(MAKE) -C ./lib/ft_printf

$(MLX42):
	@git clone $(MLX_REPO) $(MLX_DIR)
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

clean:
	$(MAKE) clean -C ./lib/libft
	$(MAKE) clean -C ./lib/ft_printf
	$(RM) -r $(OBJ_DIR)
	$(RM) -r $(MLX_DIR)

fclean: clean
	$(MAKE) fclean -C ./lib/libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re