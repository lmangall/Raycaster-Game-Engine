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
INCLUDE = -I./include

AR = ar -rcs

SRC_FILES = ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_easy_realloc.c \
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
		ft_strstr.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		get_next_line.c \
		get_next_line_utils.c \
		putnbr_with_itoa.c \
		putunbr_with_itoa.c \
		ft_printf.c \
		ft_parse_char.c \
		ft_parse_str.c \
		ft_parse_int.c \
		ft_parse_uint.c \
		ft_parse_ptr.c \
		ft_parse_hex.c \
		ft_putchar.c \
		ft_putstr.c \
		ft_putnbr.c \
		ft_putunbr.c \
		ft_puthex.c 

SOURCES = $(addprefix $(SRCS_PATH)/, $(SRC_FILES))
OBJECTS = $(addprefix $(OBJS_PATH)/, $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) $(NAME) $(OBJECTS)
	ranlib $(NAME)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c
	@mkdir -p $(OBJS_PATH)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(RM) -r $(OBJS_PATH)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re