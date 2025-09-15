#ifndef MINIRT_H
#define MINIRT_H

#include <stdio.h>
#include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>


# define W_W 1900
# define W_H 1000
# define I_W 1900
# define I_H 1000
# define BUFFER_SIZE 50
//////////////////////////// parsing ////////////////////////////
int	ft_atoi(char *nptr, int x);
int	ft_isalpha(int c);
int	ft_isdigit(int x);
char	*ft_strdup(char *s);
size_t	ft_strlen(char *str);
int	checker(char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *str, int c);
char	*handle_buffer(char **boby);
char	*get_next_line(int fd);
char	*ft_strldup(char *s, int i);

#endif








