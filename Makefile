NAME	=	bin/test
SRC		=	srcs/main.c
OBJ		=	$(SRC:.c=.o)

NAME1	=	bin/test1
SRC1	=	srcs/base_noclose.c
OBJ1	=	$(SRC1:.c=.o)

NAME2	=	bin/test2
SRC2	=	srcs/base_close.c
OBJ2	=	$(SRC2:.c=.o)

OBJS	=	$(OBJ) $(OBJ1) $(OBJ2)

NAMES	=	$(NAME) $(NAME1) $(NAME2)


HEADER	=	test.h

RM		=	rm -f

CC		=	clang

CFLAGS	=	-Wall -Wextra -I./libft/ -I./includes
#CFLAGS	+= -Werror

SYS		:=	$(shell uname)

ifeq ($(SYS), Darwin)
  CFLAGS	+=	-I./includes/MacOs -I./minilibx_macos/
  LDFLAGS	+=	-framework OpenGL -framework AppKit -L./minilibx_macos -lmlx
  MLX		= minilibx_macos/libmlx.a
else
  MLX_LINUX_PATH	=	minilibx_linux_with_destroy/
  CFLAGS	+= -I./includes/Linux -I./$(MLX_LINUX_PATH)
  LDFLAGS +=	-lXext -lX11 -L./$(MLX_LINUX_PATH) -lmlx_Linux -lpthread  -D_REENTRANT -DLinux -lbsd
  MLX		= $(MLX_LINUX_PATH)libmlx.a
endif

%.o : %.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME) $(NAME1) $(NAME2)

$(NAME) : $(OBJ)
		@echo "Compiled for $(SYS)"
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

$(NAME1) : $(OBJ1)
		$(CC) $(OBJ1) -o $(NAME1) $(LDFLAGS)

$(NAME2) : $(OBJ2)
		$(CC) $(OBJ2) -o $(NAME2) $(LDFLAGS)

clean :
		$(RM) $(OBJS)

fclean : clean
		$(RM) $(NAMES)

re	:	fclean all

.PHONY	: clean fclean re
