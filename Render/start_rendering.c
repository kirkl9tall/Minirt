#include "../minirt.h"

t_ray	generate_ray(t_mini *mini, int screen_x, int screen_y)
{
	t_ray	ray;
	t_vec3	pixel_pos;
	double	vp_x;
	double	vp_y;

	vp_x = (2.0 * ((screen_x + 0.5) / W_W) - 1.0) * (mini->cam.width_canva
			/ 2.0);
	vp_y = (1.0 - 2.0 * ((screen_y + 0.5) / W_H)) * (mini->cam.height_canva
			/ 2.0);
	ray.origin = mini->cam.pos;
	pixel_pos = vect_addi(mini->cam.pos, vect_addi(vect_multi(mini->cam.right_v,
					vp_y), vect_multi(mini->cam.up_v, vp_x)));
	pixel_pos = vect_addi(pixel_pos, mini->cam.orient);
	ray.direction = vect_normalized(vect_subs(pixel_pos, mini->cam.pos));
	return (ray);
}

int	hit_plane(t_ray ray, t_plan *plane, t_hit *hit)
{
	double	n;
	t_vec3	p0_to_origin;
	double	t;

	n = vect_prod(plane->nnv_plan, ray.direction);
	if (fabs(n) < 1e-6)
		return (1);
	p0_to_origin = vect_subs(plane->cor_plan, ray.origin);
	t = vect_prod(p0_to_origin, plane->nnv_plan) / n;
	if (t <= 0)
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
	double	h;
	double	c;
	double	discriminant;
	double	sqrt_d;
	double	t1;
	double	t2;
	double	t;

	oc = vect_subs(ray.origin, sphere->sph_center);
	a = vect_prod(ray.direction, ray.direction);
	h = vect_prod(oc, ray.direction);
	c = vect_prod(oc, oc) - (sphere->s_diam * sphere->s_diam) / 4.0;
	discriminant = h * h - 4 * a * c;
	if (discriminant < 0)
		return (0);
	sqrt_d = sqrt(discriminant);
	t1 = (-h - sqrt_d) / a;
	t2 = (-h + sqrt_d) / a;
	if (t1 < t2)
		t = t1;
	else
		t = t2;
	if (t <= 0)
		return (0);
	hit->t = t;
	hit->point = vect_addi(ray.origin, vect_multi(ray.direction, t));
	hit->normal = vect_normalized(vect_subs(hit->point, sphere->sph_center));
	hit->color = sphere->color;
	return (1);
}

int	find_closest_hit(t_mini *mini, t_ray ray, t_hit *hit)
{
	int		hit_anything;
	double	closest_so_far;
	t_hit	temp_hit;

	hit_anything = 0;
	closest_so_far = INFINITY;
	while (mini->sph)
	{
		if (hit_sphere(ray, mini->sph, &temp_hit)
			&& temp_hit.t < closest_so_far)
		{
			closest_so_far = temp_hit.t;
			*hit = temp_hit;
			hit_anything = 1;
		}
		mini->sph = mini->sph->next;
	}
	while (mini->plane)
	{
		if (hit_plane(ray, mini->plane, &temp_hit)
			&& temp_hit.t < closest_so_far)
		{
			closest_so_far = temp_hit.t;
			*hit = temp_hit;
			hit_anything = 1;
		}
		mini->plane = mini->plane->next;
	}
	while (mini->cy)
	{
		if (hit_cylinder(ray, mini->cy, &temp_hit)// TODO 
			&& temp_hit.t < closest_so_far)
		{
			closest_so_far = temp_hit.t;
			*hit = temp_hit;
			hit_anything = 1;
		}
		mini->cy = mini->cy->next;
	}
	return (hit_anything);
}

t_vec3	ray_trace(t_mini *mini, t_ray ray)
{
	t_hit	hit;
	t_vec3	color;

	color = (t_vec3){0};
	if (find_closest_hit(mini, ray, &hit))
		// color = calculate_lighting(mini, hit); TODO
		return (color);
}

void	render_scene(t_mini *mini)
{
	t_ray	ray;
	t_vec3	color;
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
            //my_put_pixel();// TODO LATER
		}
	}
	mlx_put_image_to_window(mini->mlx_utils.mlx, mini->mlx_utils.win,
		mini->mlx_utils.img, 0, 0);
}
