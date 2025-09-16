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

typedef struct s_vec3
{
	double       x;
	double		y;
	double		z;
}t_vec3;

typedef struct s_amb
{
    float alr;
    int color;
}t_amb;


typedef struct s_cam
{
    t_vec3 pos;
    t_vec3 orient;
    double fov;
}t_cam;

typedef struct s_light
{
    t_vec3 light_point;
    double lbr;
    int color;
}t_light;

typedef struct s_sphere
{
    t_vec3 sph_center;
    double  s_diam;
    int color;
}t_sphere;

typedef struct s_plan
{
    t_vec3 cor_plan;
    t_vec3 nnv_plan;
    int color;
}t_plan;

typedef struct s_cylin
{
    t_vec3 cy_center;
    t_vec3 nv_cy;
    double  cy_diam;
    double cy_height;
    int color;
}t_cylin;

typedef struct s_mini
{
    void			*mlx;
	void			*win;
    char **pars;
    char *file;
    t_cylin *cy;
    t_cam   *cam;
    t_plan  *plane;
    t_sphere *sph;
    t_light *light;
    t_amb   *amb;

}t_mini;


//////////////////////////// parsing ////////////////////////////
int	ft_atoi(char *nptr);
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
int check_file_mini(char *argv);
int  init_mini (t_mini *mini, char * title);
void parsing(int fd,t_mini *mini);
double ft_atoi_double(char *nptr);
char	**ft_split(char *s, char c);




#endif








