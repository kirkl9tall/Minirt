SRCS = get_next_line_utils.c get_next_line.c utils_pars.c \
       ft_split.c parsing.c  camera.c vec_maths.c main.c 

OBJS = $(SRCS:.c=.o)

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -I. -I/home/abismail/Desktop/minirt/minilibx-linux
MLX_DIR = /home/abismail/Desktop/minirt/minilibx-linux
LDFLAGS = -L$(MLX_DIR) -L/usr/lib
LDLIBS  = -lmlx -lXext -lX11 -lm -lz -g

RM = rm -rf
NAME = minirt

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean all re fclean
