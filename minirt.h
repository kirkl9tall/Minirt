/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m45kf4c3 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:58:25 by m45kf4c3          #+#    #+#             */
/*   Updated: 2025/10/20 15:58:26 by m45kf4c3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "GC/gc.h"
# include "GNL/gnl.h"
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h> //forbiden memset
# include <unistd.h>

# define W_W 720
# define W_H 720

typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct s_amb
{
	float			alr;
	t_vec3			color;
}					t_amb;

typedef struct s_cam
{
	t_vec3			pos;
	t_vec3			orient;
	t_vec3			up_v;
	t_vec3			right_v;
	double			width_canva;
	double			height_canva;
	double			fov;

}					t_cam;

typedef struct s_light
{
	t_vec3			light_point;
	double			lbr;
	int			color;
}					t_light;

typedef struct s_sphere
{
	t_vec3			sph_center;
	double			s_diam;
	int			color;
	struct s_sphere	*next;
}					t_sphere;

typedef struct s_plan
{
	t_vec3			cor_plan;
	t_vec3			nnv_plan;
	int			color;
	struct s_plan	*next;
}					t_plan;

typedef struct s_cylin
{
	t_vec3			cy_center;
	t_vec3			nv_cy;
	double			cy_diam;
	double			cy_height;
	int			color;
	struct s_cylin	*next;
}					t_cylin;

typedef struct s_ray
{
	t_vec3			origin;
	t_vec3			direction;
}					t_ray;
typedef struct s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				size_line;
	int				endian;
}					t_mlx;
typedef struct s_hit
{
    double      t;
    t_vec3      point;
    t_vec3      normal;
    int      color;
} t_hit;


typedef struct s_mini
{
	t_mlx			mlx_utils;
	char			**pars;
	char			*file;
	t_cylin			*cy;
	t_cam			cam;
	t_plan			*plane;
	t_sphere		*sph;
	t_light			light;
	t_amb			amb;
	t_gc			*gc;

}					t_mini;

//////////////////////////// parsing ////////////////////////////
int					ft_atoi(char *nptr);
int					ft_isalpha(int c);
int					ft_isdigit(int x);
char				*ft_strdup(char *s, t_gc **gc);
size_t				ft_strlen(char *str);
int					checker(char *str, int c);
char				*ft_strjoin(char *s1, char *s2, t_gc **gc);
char				*ft_strchr(char *str, int c);
char				*handle_buffer(char **boby);
char				*get_next_line(int fd, t_gc **gc);
char				*ft_strldup(char *s, int i);
int					check_file_mini(char *argv);
int					init_mini(t_mini *mini, char *title);
void				parsing(int fd, t_mini *mini);
double				ft_atoi_double(char *nptr, double min, double max);
char				**ft_split(char *s, char c, t_gc **gc);
void				assigner(t_mini *mini, char **splited);

////////////////////////////// camera projection

void				project_camera(t_mini *mini);

////vect_math//////////////////////////////////
t_vec3				vect_addi(t_vec3 v1, t_vec3 v2);
t_vec3				vect_subs(t_vec3 v1, t_vec3 v2);
t_vec3				vect_multi(t_vec3 v1, double prod);
double				vect_prod(t_vec3 v1, t_vec3 v2);
t_vec3				vect_cross(t_vec3 v1, t_vec3 v2);
t_vec3				vect_normalized(t_vec3 v1);
///////////////////////////////////////////////
void				render_scene(t_mini *mini);
#endif
