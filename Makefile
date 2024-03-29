
NAME	= cub3D
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -O3 -ffast-math -g


LIBFT= lib/libft/libft.a

LIBMLX42 = MLX42/build/libmlx42.a

FLAGS_MLX = -ldl -lglfw -pthread -lm
INCLUDES = -I./include -I./src/parser -I./MLX42/include/MLX42 -I/usr/local/Cellar/glfw/3.3.9/include/GLFW -I./lib/libft/include
LIB = -L/usr/local/Cellar/glfw/3.3.9/lib
ARCH = $(shell uname -m)
ifeq ($(ARCH),arm64)
    FLAGS_MLX = $(shell pkg-config --libs glfw3) -framework Cocoa -framework OpenGL -framework IOKit -L/opt/homebrew/lib
  	INCLUDES = -I./include -I./src/parser -I./MLX42/include/MLX42 -I./lib/libft/include -I$(shell echo $$HOME)/.brew/opt/glfw/include
# $(info ARM architecture detected, FLAGS_MLX changed to $(FLAGS_MLX) and INCLUDES changed to $(INCLUDES))
endif

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	CFLAGS += -fsanitize=address -g -O1
# $(info "Darwin OS detected, CFLAGS changed to $(CFLAGS))
endif

GREEN   = \033[32;1m
RESET	= \033[0m

LIBFT_DIR = lib/libft/
MLX42_DIR = ./MLX42
SRC_DIR = src
OBJ_DIR = obj

SRCS	= main.c \
		utils.c \
    	caster_to_renderer/init.c \
    	caster_to_renderer/render.c \
    	caster_to_renderer/render_utils.c \
    	caster_to_renderer/exit.c \
    	caster_to_renderer/movement_is_wall.c \
    	caster_to_renderer/movement_apply.c \
    	caster_to_renderer/movement_key.c \
    	caster_to_renderer/raycasting.c \
    	caster_to_renderer/raycasting_utils.c \
    	caster_to_renderer/raycasting_collision.c \
    	caster_to_renderer/load_textures.c \
		parser/parser.c \
		parser/parse_file.c \
		parser/parse_file_utils.c \
		parser/process_map_elements.c \
		parser/process_map_content.c \
		parser/utils_free.c \
		parser/init_parser.c \
		parser/process_map_content_height_width.c \
		parser/process_map_content_checks.c \
		parser/process_map_content_check_spaces.c \
		parser/utils_prints.c \
		parser/process_map_elements_rgb.c \
		parser/process_map_elements_rgb_utils.c \
		parser/utils_prints_elements.c \
		parser/process_map_content_check_spaces_utils.c \
		bonus/minimap_init.c \
		bonus/minimap_render.c \
		bonus/minimap.c

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
	@cd $(MLX42_DIR) && cmake -B build && cmake --build build -j4
	@echo "$(GREEN) MLX42 built $(RESET)"

check_MLX42:
		@if ! [ -d "$(MLX42_DIR)" ]; then \
	git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_DIR); \
	fi

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c include/cub3d.h
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(MAKE) clean -s -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN) Cleaned $(RESET)"

fclean: clean
	@make fclean -s -C $(LIBFT_DIR)
	@rm -rf $(MLX42_DIR)
	@rm -f $(NAME)
	@echo "$(GREEN) Full cleaned $(RESET)"

re: fclean all

.PHONY: all clean fclean re
