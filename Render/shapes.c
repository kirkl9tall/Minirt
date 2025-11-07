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

int caps(t_ray ray, t_cylin *cy, t_hit *hit,t_vec3 center_cap ,int u)
{
	double t;
	double denominator;
	t_vec3 hit_point;

	denominator = vect_prod(ray.direction,vect_normalized(cy->nv_cy));

	if (fabs(denominator) < 0)
        return 0;
	t = vect_prod(vect_subs(center_cap,ray.origin),vect_normalized(cy->nv_cy)) / denominator ;
	if (t < 0 || t < hit->t)
        return 0;
	hit_point = vect_addi(ray.origin,vect_multi(ray.direction,t));

	if (vect_len(vect_subs(hit_point, center_cap)) <= cy->cy_diam / 2 )
	{
	printf("hit->color%d\n" ,((int)cy->color.x << 16) | ((int)cy->color.y << 8) | (int)cy->color.z);

    hit->t = t;
    hit->point = hit_point;
	if(u == 1)
    	hit->normal = vect_normalized(cy->nv_cy);
	else
    	hit->normal = vect_normalized(vect_multi(cy->nv_cy , -1));
    hit->color = cy->color;
    return 1;
}
	return 0;
}

// int caps(t_ray ray, t_cylin *cy, t_hit *hit, t_vec3 center_cap, int u)
// {
//     double t;
//     double denominator;
//     t_vec3 hit_point;

//     denominator = vect_prod(ray.direction, vect_normalized(cy->nv_cy));

//     if (fabs(denominator) < 1e-6)
//         return 0;
    
//     t = vect_prod(vect_subs(center_cap, ray.origin), vect_normalized(cy->nv_cy)) / denominator;
    
//     if (t < 1e-6 || t >= hit->t)
//         return 0;
    
//     hit_point = vect_addi(ray.origin, vect_multi(ray.direction, t));

//     if (vect_len(vect_subs(hit_point, center_cap)) <= cy->cy_diam / 2)
//     {
//         hit->t = t;
//         hit->point = hit_point;
//         if (u == 1)
//             hit->normal = vect_normalized(cy->nv_cy);
//         else
//             hit->normal = vect_normalized(vect_multi(cy->nv_cy, -1));
//         hit->color = cy->color;
//         return 1;
//     }
//     return 0;
// }

// int hit_cylinder(t_ray ray, t_cylin *cy, t_hit *hit)
// {
//     t_vec3 oc;
//     double a;
//     double b;
//     double c;
//     double delta;
//     t_vec3 p;
//     t_vec3 z;
//     double x1;
//     double x2;
//     double x;
//     double sqrt_d;
//     int hit_body = 0;
//     t_vec3 normalized_axis = vect_normalized(cy->nv_cy);
    
//     oc = vect_subs(ray.origin, cy->cy_center);
//     p = vect_subs(oc, vect_multi(normalized_axis, vect_prod(normalized_axis, oc)));
//     z = vect_subs(ray.direction, vect_multi(normalized_axis, vect_prod(normalized_axis, ray.direction)));
//     a = vect_prod(z, z);
//     b = 2 * (vect_prod(p, z));
//     c = vect_prod(p, p) - ((cy->cy_diam / 2) * (cy->cy_diam / 2));

//     delta = b * b - 4 * (a * c);
//     if (delta < 0)
//         return 0;
    
//     sqrt_d = sqrt(delta);
//     x1 = (-b - sqrt_d) / (2.0 * a);
//     x2 = (-b + sqrt_d) / (2.0 * a);
    
//     if (x1 < 1e-6 && x2 < 1e-6)
//         return 0;

//     if (x1 > 1e-6 && x2 > 1e-6)
//         x = fmin(x1, x2);
//     else if (x1 > 1e-6)
//         x = x1;
//     else
//         x = x2;
    
//     if (x < hit->t)
//     {
//         t_vec3 hit_point = vect_addi(ray.origin, vect_multi(ray.direction, x));
//         double h = vect_prod(vect_subs(hit_point, cy->cy_center), normalized_axis);
        
//         // FIX: Cylinder extends from -height/2 to +height/2 from center
//         if (h >= -(cy->cy_height / 2) && h <= (cy->cy_height / 2))
//         {
//             hit->t = x;
//             hit->color = cy->color;
//             hit->point = hit_point;
//             t_vec3 tmp = vect_subs(hit->point, cy->cy_center);
//             t_vec3 proj = vect_multi(normalized_axis, vect_prod(normalized_axis, tmp));
//             hit->normal = vect_normalized(vect_subs(tmp, proj));
//             hit_body = 1;
//         }
//     }
    
//     // Check caps
//     t_vec3 cap_top = vect_addi(cy->cy_center, vect_multi(normalized_axis, (cy->cy_height / 2)));
//     t_vec3 cap_bottom = vect_subs(cy->cy_center, vect_multi(normalized_axis, (cy->cy_height / 2)));
    
//     int hit_top = caps(ray, cy, hit, cap_top, 1);
//     int hit_bottom = caps(ray, cy, hit, cap_bottom, 0);
    
//     return (hit_body || hit_top || hit_bottom);
// }

int	hit_cylinder(t_ray ray, t_cylin *cy, t_hit *hit)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	delta;
	t_vec3 p;
	t_vec3 z;
	double x1;
	double x2;
	double x;
	double sqrt_d;
	
	oc = vect_subs(ray.origin , cy->cy_center);
	p = vect_subs(oc,vect_multi(cy->nv_cy,vect_prod(cy->nv_cy,oc)));
	z = vect_subs(ray.direction, vect_multi(cy->nv_cy,vect_prod(cy->nv_cy,ray.direction)));
	a = vect_prod(z,z);
	b = 2 * (vect_prod(p,z));
	c = vect_prod(p,p) - ((cy->cy_diam/2) * (cy->cy_diam/2));

	delta = b * b - 4 * (a * c);
	if (delta  < 0)
		return  0;
	sqrt_d = sqrt(delta);
	x1 = (-b - sqrt_d) / (2.0 * a);
	x2 = (-b + sqrt_d) / (2.0 * a);
	if (x1 < 1e-6 && x2 < 1e-6)
    	return 0;

	if (x1 > 0 && x2 > 0)
	x = fmin(x1,x2);
	else if (x1 > 0)
	x = x1;
	else if (x2 > 0 )
	x = x2;
	if (x < hit->t)
	{
		t_vec3 hit_point = vect_addi(ray.origin, vect_multi(ray.direction, x));
    	double h = vect_prod(vect_subs(hit_point, cy->cy_center), cy->nv_cy);
    	if (h < 0 || h > cy->cy_height)
        	return 0;
		hit->t = x;
		hit->color = cy->color;
		cy->nv_cy = vect_normalized(cy->nv_cy);
		hit->point = vect_addi(ray.origin , vect_multi(ray.direction,x));
		t_vec3 tmp = vect_subs(hit->point, cy->cy_center);
		t_vec3 proj = vect_multi(cy->nv_cy, vect_prod(cy->nv_cy, tmp));
		hit->normal = vect_normalized(vect_subs(tmp, proj));
		t_vec3 cap_top = vect_addi(cy->cy_center,vect_multi(cy->nv_cy,(cy->cy_height/2)));
		t_vec3 cap_bott = vect_subs(cy->cy_center,vect_multi(cy->nv_cy,(cy->cy_height/2)));
		int hit_top = caps(ray,cy,hit,cap_top , 1);
		int hit_bottom = caps(ray,cy,hit,cap_bott ,0);
		return 1;
	}
	return (0);
}


int	find_closest_hit(t_mini *mini, t_ray ray, t_hit *hit)
{
	int			hit_anything;
	double		closest_so_far;
	t_hit		temp_hit;
	t_sphere	*current_sph;
	t_plan		*current_plane;
	t_cylin		*current_cylinder;
	current_cylinder = mini->cy;
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
	while (current_cylinder)
	{
		temp_hit.t = closest_so_far;
		if (hit_cylinder(ray, current_cylinder, &temp_hit)
		&& temp_hit.t < closest_so_far)
		{
			closest_so_far = temp_hit.t;
			*hit = temp_hit;
			hit_anything = 1;
		}
		current_cylinder = current_cylinder->next;
	}
	return (hit_anything);
}


