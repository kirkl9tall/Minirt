SRCS = get_next_line_utils.c get_next_line.c utils_pars.c \
       ft_split.c parsing.c main.c 

OBJS = $(SRCS:.c=.o)

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -I. -I/home/the-worst/Desktop/Minirt/minilibx-linux
MLX_DIR = /home/the-worst/Desktop/Minirt/minilibx-linux
LDFLAGS = -L$(MLX_DIR) -L/usr/lib
LDLIBS  = -lmlx_Linux -lXext -lX11 -lm -lz -g

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
