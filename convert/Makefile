NAME	=	convert

SRCS		=	main.c

SRC	=	$(addprefix src/, $(SRCS))

OBJ			=	$(SRC:.c=.o)

HEADER	=	test.h	\
					libft/libft.h

RM		=	rm -f

CC		=	clang

CFLAGS	=	-Wall -Wextra -I./libs/libft/ -I./includes/
#CFLAGS	+= -Werror

LDFLAGS	=	-L./libs/libft/ -lft

SYS		:=	$(shell uname)

ifeq ($(SYS), Darwin)
  CFLAGS	+=	-I./includes/MacOs -I./libs/minilibx_macos/
  LDFLAGS	+=	-framework OpenGL -framework AppKit -L./libs/minilibx_macos -lmlx
  MLX		= libs/minilibx_macos/libmlx.a
else
  MLX_LINUX_PATH	=	libs/mlx/
  CFLAGS	+=  -I./$(MLX_LINUX_PATH)
  LDFLAGS +=	-lXext -lX11 -L./$(MLX_LINUX_PATH) -lmlx_Linux -lbsd
  MLX		= $(MLX_LINUX_PATH)libmlx.a
endif


%.o : %.c $(HEADER)
		$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean :
		$(RM) $(OBJ)

fclean : clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	: clean fclean re
