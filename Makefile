NAME		=	fdf
CFLAGS		=	-Wall -Wextra -Werror
CC			=	gcc
MAKE		=	make

HEADERS		=	fdf.h
INCLUDE		=	.
SRCS		=	main.c events.c fdf.c \
				render/utils.c render/draw_line.c render/display.c \
				parsing/parse.c parsing/get_next_line.c parsing/get_next_line_utils.c \
				parsing/ft_split.c parsing/ft_atoi.c parsing/ft_atoi_hex.c
MLX_DIR		=	minilibx
MLX			=   $(MLX_DIR)/libmlx_Linux.a
OBJS		=	$(patsubst %.c,%.o,$(SRCS))

all : $(NAME)

$(NAME): $(OBJS) $(HEADERS) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L $(MLX_DIR) -lmlx -lX11 -lXext -lm
$(MLX):
	cd minilibx && $(MAKE)

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -I $(MLX_DIR) -I $(INCLUDE) -c $< -o $@

clean :
	rm -f $(OBJS)
	cd minilibx && $(MAKE) clean

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re

