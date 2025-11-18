/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 15:58:25 by m45kf4c3          #+#    #+#             */
/*   Updated: 2025/11/18 17:05:28 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "gc/gc.h"
# include "gnl/gnl.h"
# include "/usr/include/minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define W_W 800
# define W_H 600

typedef struct s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;
typedef struct s_equa
{
	t_vec3			oc;
	double			a;
	double			b;
	double			c;
	double			delta;
	double			x1;
	double			x2;
	double			x;
	double			sqrt_d;
}					t_equa;

typedef struct s_amb
{
	float			alr;
	t_vec3			color;
}					t_amb;

typedef struct s_cam
{
	double			width_canva;
	double			height_canva;
	double			fov;
	t_vec3			pos;
	t_vec3			orient;
	t_vec3			up_v;
	t_vec3			right_v;

}					t_cam;

typedef struct s_light
{
	double			lbr;
	t_vec3			color;
	t_vec3			light_point;
}					t_light;

typedef struct s_sphere
{
	double			s_diam;
	t_vec3			color;
	t_vec3			sph_center;
	struct s_sphere	*next;
}					t_sphere;

typedef struct s_plan
{
	t_vec3			color;
	t_vec3			cor_plan;
	t_vec3			nnv_plan;
	struct s_plan	*next;
}					t_plan;

typedef struct s_cylin
{
	int				hit_top;
	int				hit_bottom;
	double			cy_diam;
	double			cy_height;
	t_vec3			z;
	t_equa			f;
	t_vec3			p;
	t_vec3			oc;
	t_vec3			tmp;
	t_vec3			proj;
	t_vec3			color;
	t_vec3			nv_cy;
	t_vec3			cap_top;
	t_vec3			cy_center;
	t_vec3			hit_point;
	t_vec3			cap_bottom;
	t_vec3			normalized_axis;
	int				u_cap;
	struct s_cylin	*next;
}					t_cylin;

typedef struct s_ray
{
	t_vec3			origin;
	t_vec3			direction;
}					t_ray;
typedef struct s_mlx
{
	int				bpp;
	int				endian;
	int				size_line;
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
}					t_mlx;
typedef struct s_hit
{
	t_vec3			color;
	double			t;
	t_vec3			point;
	t_vec3			normal;
}					t_hit;

typedef struct s_fch
{
	int				hit_anything;
	double			closest_so_far;
	t_hit			temp_hit;
	t_sphere		*current_sph;
	t_plan			*current_plane;
	t_cylin			*current_cylinder;
}					t_fch;
typedef struct s_mini
{
	t_gc			*gc;
	t_amb			amb;
	t_cylin			*cy;
	t_cam			cam;
	t_sphere		*sph;
	t_light			light;
	t_plan			*plane;
	t_mlx			mlx_utils;

}					t_mini;

//////////////////////////// parsing ////////////////////////////
int					ft_isalpha(int c);
int					ft_isdigit(int x);
int					ft_atoi(char *nptr);
size_t				ft_strlen(char *str);
int					checker(char *str, int c);
char				*handle_buffer(char **boby);
char				*ft_strldup(char *s, int i);
int					check_file_mini(char *argv);
char				*ft_strchr(char *str, int c);
void				parsing(int fd, t_mini *mini);
char				*ft_strdup(char *s, t_gc **gc);
char				*get_next_line(int fd, t_gc **gc);
int					init_mini(t_mini *mini, char *title);
char				**ft_split(char *s, char c, t_gc **gc);
void				assigner(t_mini *mini, char **splited);
char				*ft_strjoin(char *s1, char *s2, t_gc **gc);
double				ft_atoi_double(char *nptr, double min, double max);
void				project_camera(t_mini *mini);
t_vec3				vect_normalized(t_vec3 v1);
t_vec3				vect_addi(t_vec3 v1, t_vec3 v2);
t_vec3				vect_subs(t_vec3 v1, t_vec3 v2);
double				vect_prod(t_vec3 v1, t_vec3 v2);
t_vec3				vect_cross(t_vec3 v1, t_vec3 v2);
t_vec3				vect_multi(t_vec3 v1, double prod);
void				render_scene(t_mini *mini);
int					hit_plane(t_ray ray, t_plan *plane, t_hit *hit);
int					hit_cylinder(t_ray ray, t_cylin *cy, t_hit *hit);
int					hit_sphere(t_ray ray, t_sphere *sphere, t_hit *hit);
int					find_closest_hit(t_mini *mini, t_ray ray, t_hit *hit);
t_vec3				add_light_shadow(t_mini *mini, t_hit hit);
double				vect_len(t_vec3 v1);
void				*ft_memset(void *s, int c, size_t n);
int					euqation_cylinder(t_ray ray, t_cylin *cy, t_equa *f);
void				assign_params_cy(t_cylin *cy, char **splited, t_mini *mini,
						char **splited_comma);
void				past_cy(t_mini *mini, t_cylin *cy);
void				past_pl(t_mini *mini, t_plan *plane);
void				assign_params_pl(t_plan *plane, char **splited,
						t_mini *mini, char **splited_comma);
int					count_split(char **splited);
void				assign_cy(t_mini *mini, char **splited);
void				past_cy(t_mini *mini, t_cylin *cy);
int					ft_strcmp(const char *s1, const char *s2);
void				cleaner_exit(void);
double				atoi_loop(char *nptr, double num);
void				error_pinting(char *error);
void				assign_a(t_mini *mini, char **splited);
void				assign_c(t_mini *mini, char **splited);
void				assign_l(t_mini *mini, char **splited);
void				assign_pl(t_mini *mini, char **splited);
void				assign_sph(t_mini *mini, char **splited);
void				past_sph(t_mini *mini, t_sphere *sph);
int					caps(t_ray ray, t_cylin *cy, t_hit *hit, t_vec3 center_cap);
void				init(t_hit *hit, t_equa f, t_cylin *cy);
void				norm_v1(t_cylin *cy, t_ray ray, t_hit *hit);
#endif
