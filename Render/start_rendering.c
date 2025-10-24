#include "../minirt.h"

t_ray	generate_ray(t_mini *mini, int screen_x, int screen_y)
{
	t_ray	ray;
	double	vp_x;
	double	vp_y;
	t_vec3	direction;

	vp_x = (2.0 * ((screen_x + 0.5) / W_W) - 1.0) * (mini->cam.width_canva
			/ 2.0);
	vp_y = (1.0 - 2.0 * ((screen_y + 0.5) / W_H)) * (mini->cam.height_canva
			/ 2.0);
	ray.origin = mini->cam.pos;
	direction.x = mini->cam.orient.x + mini->cam.right_v.x * vp_x
		+ mini->cam.up_v.x * vp_y;
	direction.y = mini->cam.orient.y + mini->cam.right_v.y * vp_x
		+ mini->cam.up_v.y * vp_y;
	direction.z = mini->cam.orient.z + mini->cam.right_v.z * vp_x
		+ mini->cam.up_v.z * vp_y;
	ray.direction = vect_normalized(direction);
	return (ray);
}
int	hit_plane(t_ray ray, t_plan *plane, t_hit *hit)
{
	double	n;
	t_vec3	p0_to_origin;
	double	t;

	n = vect_prod(plane->nnv_plan, ray.direction);
	if (fabs(n) < 1e-6)
		return (0);
	p0_to_origin = vect_subs(plane->cor_plan, ray.origin);
	t = vect_prod(p0_to_origin, plane->nnv_plan) / n;
	if (t <= 1e-6)
		return (0);
	hit->t = t;
	hit->point = vect_addi(ray.origin, vect_multi(ray.direction, t));
	hit->normal = plane->nnv_plan;
	hit->color = plane->color;
	return (1);
}

int	hit_sphere(t_ray ray, t_sphere *sphere, t_hit *hit)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t;
	double	sqrt_d;
	double	t1;
	double	t2;

	oc = vect_subs(ray.origin, sphere->sph_center);
	a = vect_prod(ray.direction, ray.direction);
	b = 2.0 * vect_prod(oc, ray.direction);
	c = vect_prod(oc, oc) - (sphere->s_diam * sphere->s_diam) / 4.0;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	sqrt_d = sqrt(discriminant);
	t1 = (-b - sqrt_d) / (2.0 * a);
	t2 = (-b + sqrt_d) / (2.0 * a);
	if (t1 > 1e-6)
		t = t1;
	else if (t2 > 1e-6)
		t = t2;
	else
		return (0);
	hit->t = t;
	hit->point = vect_addi(ray.origin, vect_multi(ray.direction, t));
	hit->normal = vect_normalized(vect_subs(hit->point, sphere->sph_center));
	hit->color = sphere->color;
	return (1);
}

int	hit_cylinder(t_ray ray, t_cylin *cy, t_hit *hit)
{
	(void)ray;
	(void)cy;
	(void)hit;
	return (0);
}

int	find_closest_hit(t_mini *mini, t_ray ray, t_hit *hit)
{
	int			hit_anything;
	double		closest_so_far;
	t_hit		temp_hit;
	t_sphere	*current_sph;
	t_plan		*current_plane;

	hit_anything = 0;
	closest_so_far = INFINITY;
	current_sph = mini->sph;
	while (current_sph)
	{
		if (hit_sphere(ray, current_sph, &temp_hit)
			&& temp_hit.t < closest_so_far)
		{
			closest_so_far = temp_hit.t;
			*hit = temp_hit;
			hit_anything = 1;
		}
		current_sph = current_sph->next;
	}
	current_plane = mini->plane;
	while (current_plane)
	{
		if (hit_plane(ray, current_plane, &temp_hit)
			&& temp_hit.t < closest_so_far)
		{
			closest_so_far = temp_hit.t;
			*hit = temp_hit;
			hit_anything = 1;
		}
		current_plane = current_plane->next;
	}
	return (hit_anything);
}

int	ray_trace(t_mini *mini, t_ray ray)
{
	t_hit	hit;

	if (find_closest_hit(mini, ray, &hit))
		return (hit.color); // TODO add light and ambiant
	return (0x000000);
}

void	my_put_pixel(t_mini *mini, int x, int y, int color)
{
	char	*pixel;

	pixel = mini->mlx_utils.addr + (y * mini->mlx_utils.size_line) + (x
			* (mini->mlx_utils.bpp / 8));
	*(int *)pixel = color;
}
void	render_scene(t_mini *mini)
{
	t_ray	ray;
	int		color;
	int		x;
	int		y;

	y = -1;
	while (++y < W_H)
	{
		x = -1;
		while (++x < W_W)
		{
			ray = generate_ray(mini, x, y);
			color = ray_trace(mini, ray);
			my_put_pixel(mini, x, y, color);
		}
	}
	mlx_put_image_to_window(mini->mlx_utils.mlx, mini->mlx_utils.win,
		mini->mlx_utils.img, 0, 0);
}
