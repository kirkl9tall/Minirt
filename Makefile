SRCS = main.c get_next_line_utils.c get_next_line.c

OBJS = $(SRCS:.c=.o)
CC = gcc -Werror -Wextra -Wall -I.  -I/home/abismail/Desktop/minirt/minilibx-linux
CFLAGS = -L/home/abismail/Desktop/minirt/minilibx-linux
LDLIBS	=	-lmlx -lXext -lX11 -lm
RM = rm -rf
NAME = minirt

all:$(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
clean:
	$(RM)$(OBJS)
fclean:clean
	$(RM)$(NAME)
re : fclean all

.PHONY:	clean  all re fclean 
