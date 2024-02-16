NAME    = tutorial
INC     = /usr/local/include
INCFT   = ../../../lib/libft/include
# header from libft
LIBFT   = ../../../lib/libft/
LIBMLX  = ./minilibx_opengl_20191021
UNAME   := $(shell uname)# get the OS name, this will help define behaviors for certain OS's
CFLAGS  = -Wall -Werror -Wextra -O3 -g -I$(INC) -I${INCFT} -Iinclude# C Flags (gcc) & linking. "-Iinclude" if you created the folder "include" to put your project headers"
LFLAGS  = -L$(LIBMLX) -lmlx -L${LIBFT} -lft# if you decided to install libmlx.a locally you don't need "-L$(LIBMLX) -lmlx" the school also has it locally as well...
SRC     = $(wildcard src/*.c)# list your source files
OBJ     = $(SRC:%.c=%.o)# convert source files to binary list

ifeq ($(UNAME), Darwin) # iMac / macOS
	CC = gcc
	LIBMLX = ./minilibx_opengl_20191021
# LFLAGS = -L$(LIBMLX) -lmlx_Darwin -L${LIBFT} -lft -framework OpenGL -framework AppKit
	LFLAGS = -L$(LIBMLX) $(LIBMLX)/libmlx.a -L${LIBFT} -lft -framework OpenGL -framework AppKit
else ifeq ($(UNAME), FreeBSD) # FreeBSD
	CC = clang
	LFLAGS += -lbsd -lXext -lX11 -lm
else # Linux and others...
	CC = gcc
	LFLAGS += -lbsd -lXext -lX11 -lm
endif

all: $(NAME)

$(NAME): runlibft $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)

runlibft:
	make -C $(LIBFT) --no-print-directory

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)

re: fclean all

show:
	@printf "UNAME		: $(UNAME)\n"
	@printf "NAME  		: $(NAME)\n"
	@printf "CC		: $(CC)\n"
	@printf "CFLAGS		: $(CFLAGS)\n"
	@printf "LFLAGS		: $(LFLAGS)\n"
	@printf "SRC		: $(SRC)\n"
	@printf "OBJ		: $(OBJ)\n"


