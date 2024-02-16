ARCH			:=	$(shell uname -m)
ARCH_ARM64		:=	arm64

MODULE_SRC		:=	mlx_image.swift mlx_window.swift mlx_init.swift

ifeq ($(ARCH), $(ARCH_ARM64))
MODULE_OBJ		=	$(MODULE_SRC:.swift=.o)
else
MODULE_OBJ		=	$(MODULE_SRC:.swift=.swiftmodule)
endif

SRC				=	interface.swift $(MODULE_SRC)
OBJ				=	$(SRC:.swift=.o)

C_SRC			=	mlx_xpm.c mlx_png.c mlx_string_put.c
C_OBJ			=	$(C_SRC:.c=.o)
CFLAGS			=	-O3

NAME			=	libmlx.dylib

INC				=	-I.
#OPTI			=	-Ounchecked

all: $(NAME)

$(NAME): $(MODULE_OBJ) $(OBJ) $(C_OBJ)
	swiftc $(OPTI) $(INC) -o $(NAME) -emit-library $(OBJ) $(C_OBJ) -lz


ifeq ($(ARCH), $(ARCH_ARM64))
.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

%.o: %.swift
	swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@ -emit-module -module-name $(patsubst %.swift,%,$<) -module-link-name $(patsubst %.swift,%,$<)
else
%.o: %.swift
	swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@
%.swiftmodule: %.swift

	swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@ -emit-module -module-name $(patsubst %.swift,%,$<) -module-link-name $(patsubst %.swift,%,$<)
endif


clean:
	rm -f $(NAME) $(OBJ) $(MODULE_OBJ) $(C_OBJ) *.swiftdoc *~ *.swiftmodule *.swiftsourceinfo

