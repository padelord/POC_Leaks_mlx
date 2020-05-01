NAME	=	test

SRCS	=	main.c

SRC		=	$(addprefix srcs/, $(SRCS))

OBJ			=	$(SRC:.c=.o)

HEADER	=	test.h
HEADER	+=	libft/libft.h


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
  CFLAGS	+= -I./includes/Linux -I./minilibx_linux
  LDFLAGS +=	-lXext -lX11 -L./minilibx_linux -lmlx_Linux -lpthread  -D_REENTRANT -DLinux
  MLX		= minilib_linux/libmlx.a
endif

%.o : %.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@


all : $(NAME)

$(NAME) : $(OBJ)
		@echo "Compiled for $(SYS)"
		@$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean :
		$(RM) $(OBJ)

fclean : clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	: clean fclean re
