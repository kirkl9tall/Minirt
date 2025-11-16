/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 16:07:26 by zatais            #+#    #+#             */
/*   Updated: 2025/11/16 16:07:26 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
	t_equa	h;
	double	t1;
	double	t2;

	h.oc = vect_subs(ray.origin, sphere->sph_center);
	h.a = vect_prod(ray.direction, ray.direction);
	h.b = 2.0 * vect_prod(h.oc, ray.direction);
	h.c = vect_prod(h.oc, h.oc) - (sphere->s_diam * sphere->s_diam) / 4.0;
	h.delta = h.b * h.b - 4 * h.a * h.c;
	if (h.delta < 0)
		return (0);
	h.sqrt_d = sqrt(h.delta);
	t1 = (-h.b - h.sqrt_d) / (2.0 * h.a);
	t2 = (-h.b + h.sqrt_d) / (2.0 * h.a);
	if (t1 > 1e-6)
		hit->t = t1;
	else if (t2 > 1e-6)
		hit->t = t2;
	else
		return (0);
	hit->point = vect_addi(ray.origin, vect_multi(ray.direction, hit->t));
	hit->normal = vect_normalized(vect_subs(hit->point, sphere->sph_center));
	hit->color = sphere->color;
	return (1);
}

int	caps(t_ray ray, t_cylin *cy, t_hit *hit, t_vec3 center_cap, int u)
{
	double	t;
	double	denominator;
	t_vec3	hit_point;

	denominator = vect_prod(ray.direction, vect_normalized(cy->nv_cy));
	if (fabs(denominator) < 1e-6)
		return (0);
	t = vect_prod(vect_subs(center_cap, ray.origin), vect_normalized(cy->nv_cy))
		/ denominator;
	if (t < 1e-6 || t >= hit->t)
		return (0);
	hit_point = vect_addi(ray.origin, vect_multi(ray.direction, t));
	if (vect_len(vect_subs(hit_point, center_cap)) <= cy->cy_diam / 2)
	{
		hit->t = t;
		hit->point = hit_point;
		hit->normal = vect_normalized(vect_multi(cy->nv_cy, -1));
		if (u == 1)
			hit->normal = vect_normalized(cy->nv_cy);
		hit->color = cy->color;
		return (1);
	}
	return (0);
}

int	euqation_cylinder(t_ray ray, t_cylin *cy, t_equa *f)
{
	cy->oc = vect_subs(ray.origin, cy->cy_center);
	cy->p = vect_subs(cy->oc, vect_multi(cy->normalized_axis,
				vect_prod(cy->normalized_axis, cy->oc)));
	cy->z = vect_subs(ray.direction, vect_multi(cy->normalized_axis,
				vect_prod(cy->normalized_axis, ray.direction)));
	f->a = vect_prod(cy->z, cy->z);
	f->b = 2 * (vect_prod(cy->p, cy->z));
	f->c = vect_prod(cy->p, cy->p) - ((cy->cy_diam / 2) * (cy->cy_diam / 2));
	f->delta = f->b * f->b - 4 * (f->a * f->c);
	if (f->delta < 0)
		return (0);
	f->sqrt_d = sqrt(f->delta);
	f->x1 = (-f->b - f->sqrt_d) / (2.0 * f->a);
	f->x2 = (-f->b + f->sqrt_d) / (2.0 * f->a);
	if (f->x1 < 1e-6 && f->x2 < 1e-6)
		return (0);
	if (f->x1 > 1e-6 && f->x2 > 1e-6)
		f->x = fmin(f->x1, f->x2);
	else if (f->x1 > 1e-6)
		f->x = f->x1;
	else
		f->x = f->x2;
	return (1);
}

int	hit_cylinder(t_ray ray, t_cylin *cy, t_hit *hit)
{
	t_equa	f;
	int		hit_body;
	double	h;

	hit_body = 0;
	cy->normalized_axis = vect_normalized(cy->nv_cy);
	if (!euqation_cylinder(ray, cy, &f))
		return (0);
	if (f.x < hit->t)
	{
		cy->hit_point = vect_addi(ray.origin, vect_multi(ray.direction, f.x));
		h = vect_prod(vect_subs(cy->hit_point, cy->cy_center),
				cy->normalized_axis);
		if (h >= -(cy->cy_height / 2) && h <= (cy->cy_height / 2))
		{
			init(hit, f, cy);
			cy->tmp = vect_subs(hit->point, cy->cy_center);
			cy->proj = vect_multi(cy->normalized_axis,
					vect_prod(cy->normalized_axis, cy->tmp));
			hit->normal = vect_normalized(vect_subs(cy->tmp, cy->proj));
			hit_body = 1;
		}
	}
	norm_v1(cy, ray, hit);
	return (hit_body || cy->hit_top || cy->hit_bottom);
}
