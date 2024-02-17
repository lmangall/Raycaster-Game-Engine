
NAME	= minimal_animation_mlx42 
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -O3 -ffast-math -g

LIBFT_DIR = ../../../lib/libft
LIBMLX42_DIR = ./MLX42
LIBFT = $(LIBFT_DIR)/libft.a
LIBMLX42 = $(LIBMLX42_DIR)/build/libmlx42.a

FLAGS_MLX = -ldl -lglfw -pthread -lm
INCLUDES = -I./include -I./src/parser -I$(LIBMLX42_DIR)/include/MLX42 -I$(LIBFT_DIR)/lib/libft/include -I/usr/local/Cellar/glfw/3.3.9/include/GLFW
LIB = -L/usr/local/Cellar/glfw/3.3.9/lib
ARCH = $(shell uname -m)
ifeq ($(ARCH),arm64)
    FLAGS_MLX = $(shell pkg-config --libs glfw3) -framework Cocoa -framework OpenGL -framework IOKit -L/opt/homebrew/lib
	INCLUDES = -I./include -I$(LIBMLX42_DIR)/include/MLX42 -I$(LIBFT_DIR)/include -I/usr/local/Cellar/glfw/3.3.9/include/GLFW
# $(info ARM architecture detected, FLAGS_MLX changed to $(FLAGS_MLX) and INCLUDES changed to $(INCLUDES))
endif

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	CFLAGS += -fsanitize=address -g -O1
# $(info "Darwin OS detected, CFLAGS changed to $(CFLAGS))
endif

GREEN   = \033[32;1m
RESET	= \033[0m

SRC_DIR = src
OBJ_DIR = obj
HEADERS = $(wildcard include/*.h)


SRCS	= main.c

SRC	= $(addprefix $(SRC_DIR)/, $(SRCS))
# OBJ = $(addprefix $(OBJ_DIR), $(notdir $(SRC:.c=.o)))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
	OBJ := $(OBJ:/=_)

all: check_MLX42  $(NAME)

$(NAME): $(LIBFT) libmlx $(LIBMLX42) $(OBJ)
	@$(CC)  $(OBJ) $(LIBFT) $(LIBMLX42) -o $(NAME) $(CFLAGS) $(FLAGS_MLX)
	@echo "$(GREEN) Compiled with $(CFLAGS)$(RESET)"

$(LIBFT):
	@make -s -C $(LIBFT_DIR)
	@echo "$(GREEN) Libft compiled $(RESET)"

libmlx:
	@cd $(LIBMLX42_DIR) && cmake -B build && cmake --build build -j4
	@echo "$(GREEN) MLX42 built $(RESET)"

check_MLX42:
	@if ! [ -d "$(LIBMLX42_DIR)" ]; then \
	git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX42_DIR); \
	fi

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@echo "Compiling $< into $@"
	@echo "Include paths: $(INCLUDES)"
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(MAKE) clean -s -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN) Cleaned $(RESET)"

fclean: clean
	@make fclean -s -C $(LIBFT_DIR)
	@rm -rf $(LIBMLX42_DIR)
	@rm -f $(NAME)
	@echo "$(GREEN) Full cleaned $(RESET)"

re: fclean all

.PHONY: all clean fclean re
