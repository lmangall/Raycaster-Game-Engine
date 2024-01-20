# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 12:56:38 by lmangall          #+#    #+#              #
#    Updated: 2023/05/21 14:17:17 by lmangall         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS_PATH = src
OBJS_PATH = obj

CC = cc
CFLAGS = -g -Wall -Wextra -Werror

AR = ar -rcs

SRC_FILES = ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strcmp.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		get_next_line.c \
		get_next_line_utils.c \
		putnbr_with_itoa.c \
		putunbr_with_itoa.c

SOURCES = $(addprefix $(SRCS_PATH)/, $(SRC_FILES))
OBJECTS = $(addprefix $(OBJS_PATH)/, $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) $(NAME) $(OBJECTS)
	ranlib $(NAME)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
	@mkdir -p $(OBJS_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJS_PATH)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

# NAME = libft.a
# SRCS_PATH = src/
# OBJS_PATH = obj/

# CC = cc -g

# FLAGS = -Wall -Wextra -Werror

# AR = ar -rcs

# SRC_FILES = ft_atoi.c \
# 		ft_bzero.c \
# 		ft_calloc.c \
# 		ft_isalnum.c \
# 		ft_isalpha.c \
# 		ft_isascii.c \
# 		ft_isdigit.c \
# 		ft_isprint.c \
# 		ft_isspace.c \
# 		ft_itoa.c \
# 		ft_memchr.c \
# 		ft_memcmp.c \
# 		ft_memcpy.c \
# 		ft_memmove.c \
# 		ft_memset.c \
# 		ft_putchar_fd.c \
# 		ft_putendl_fd.c \
# 		ft_putnbr_fd.c \
# 		ft_putstr_fd.c \
# 		ft_split.c \
# 		ft_strchr.c \
# 		ft_strcmp.c \
# 		ft_strdup.c \
# 		ft_striteri.c \
# 		ft_strjoin.c \
# 		ft_strlcat.c \
# 		ft_strlcpy.c \
# 		ft_strlen.c \
# 		ft_strmapi.c \
# 		ft_strncmp.c \
# 		ft_strnstr.c \
# 		ft_strrchr.c \
# 		ft_strtrim.c \
# 		ft_substr.c \
# 		ft_tolower.c \
# 		ft_toupper.c \
# 		get_next_line.c\
# 		get_next_line_utils.c\

# SOURCES = $(addprefix $(SRCS_PATH), $(SRC_FILES))
# OBJECTS = $(addprefix $(OBJS_PATH), $(SRC_FILES:.c=.o))

# all: $(NAME)

# $(NAME): $(OBJECTS)
# 	@echo "$(NAME): Libft compiling..."
# 	@$(AR) $(NAME) $(OBJECTS)
# 	@echo "$(NAME): Libft complete!"

# $(OBJS_PATH)%.o: $(SRCS_PATH)%.c
# 	@mkdir -p $(OBJS_PATH)
# 	@$(CC) $(FLAGS) -c $< -o $@

# clean:
# 	@echo "$(NAME): object (*.o) files were deleted"
# 	@rm -rf $(OBJS_PATH)

# fclean: clean
# 	@echo "$(NAME) was deleted"
# 	@rm -rf $(NAME)
	
# re: fclean all

# .PHONY: all clean fclean re



# # Name of the library.
# NAME    := libft.a

# # Name of the directories.
# INC_DIR := ./src/
# SRC_DIR := ./src/

# OBJ_DIR := obj

# # Path of the directories.
# INCLS   := $(INC_DIR)
# SRCS    := $(wildcard $(SRC_DIR)/*.c)
# OBJS    := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# # Define all the compiling flags.
# CC      := gcc
# CFLAGS  += -Wall -Werror -Wextra -g
# #-fsanitize=address -fno-omit-frame-pointer
# LFLAGS  += -I.
# AR      := ar rcs
# RLIB    := ranlib

# # Compile and create everything.
# all:	obj
# 		@$(MAKE) -j $(NAME)

# # Creates the object files' directory.
# obj:
# 		@mkdir -p $(OBJ_DIR)

# # This won't run if the object files don't exist or are not modified.
# $(NAME): $(OBJS)
# 		@$(AR) $(NAME) $(OBJS)
# 		@$(RLIB) $(NAME)
# 		@echo "[INFO] $(NAME) created!"

# # This won't run if the source files don't exist or are not modified.
# $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
# 		$(CC) $(CFLAGS) -c $< -o $@ $(LFLAGS)/$(INCLS)

# # Rule to remove all the object files and directory.
# clean:
# 		@rm -rf $(OBJS) $(OBJ_DIR)
# 		@echo "[INFO] Objects removed!"

# # Rule to remove everything that has been created by the makefile.
# fclean: clean
# 		@rm -rf $(NAME) $(LIB_DIR)
# 		@echo "[INFO] Library [$(NAME)] removed!"

# # Rule to re-make everything.
# re:		fclean all

# # Unit test the library.
# test:	all
# 		@echo "Test"

# # Installs the library.
# install:test
# 		@echo "You must be root to install"

# # Makes sure that gnu make will still run even if files called
# # clean / fclean / all and re already exist in the directory
# .PHONY:	all clean fclean re test install
