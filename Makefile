SRCS = GC/gc.c GNL/gnl.c GNL/gnl_utils.c  Render/start_rendering.c \
	   pars_maths/utils_pars.c Render/shapes.c  Render/rendering_utils.c \
       pars_maths/ft_split.c pars_maths/parsing.c pars_maths/parsing2.c \
	   pars_maths/parsing3.c pars_maths/parsing4.c pars_maths/camera.c \
	   pars_maths/vec_maths.c pars_maths/vec_maths2.c main.c \

OBJS = $(SRCS:.c=.o)

CC      = cc
CFLAGS  =  -g -I$(MLX_DIR)
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

