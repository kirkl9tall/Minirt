SRCS = GC/gc.c GNL/gnl.c GNL/gnl_utils.c  Render/start_rendering.c \
	   utils_pars.c \
       ft_split.c parsing.c camera.c vec_maths.c main.c

OBJS = $(SRCS:.c=.o)

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -I$(MLX_DIR)
MLX_DIR = ./minilibx-linux
LDFLAGS = -L$(MLX_DIR)
LDLIBS  = -lmlx -lXext -lX11 -lm

RM = rm -rf
NAME = minirt

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean all re fclean

