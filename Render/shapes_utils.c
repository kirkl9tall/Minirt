/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 16:10:03 by zatais            #+#    #+#             */
/*   Updated: 2025/11/16 16:26:50 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

void	init_v2(t_mini *mini, t_fch *t)
{
	t->current_cylinder = mini->cy;
	t->hit_anything = 0;
	t->closest_so_far = INFINITY;
	t->current_sph = mini->sph;
	t->current_plane = mini->plane;
}

void	norm_v1(t_cylin *cy, t_ray ray, t_hit *hit)
{
	cy->cap_top = vect_addi(cy->cy_center, vect_multi(cy->normalized_axis,
				(cy->cy_height / 2)));
	cy->cap_bottom = vect_subs(cy->cy_center, vect_multi(cy->normalized_axis,
				(cy->cy_height / 2)));
	cy->u_cap = 1;
	cy->hit_top = caps(ray, cy, hit, cy->cap_top);
	cy->u_cap = 0;
	cy->hit_bottom = caps(ray, cy, hit, cy->cap_bottom);
}

void	init(t_hit *hit, t_equa f, t_cylin *cy)
{
	hit->t = f.x;
	hit->color = cy->color;
	hit->point = cy->hit_point;
}

int	find_closest_hit(t_mini *mini, t_ray ray, t_hit *hit)
{
	t_fch	t;

	init_v2(mini, &t);
	while (t.current_sph)
	{
		if (hit_sphere(ray, t.current_sph, &t.temp_hit)
			&& t.temp_hit.t < t.closest_so_far)
		{
			t.closest_so_far = t.temp_hit.t;
			*hit = t.temp_hit;
			t.hit_anything = 1;
		}
		t.current_sph = t.current_sph->next;
	}
	while (t.current_plane)
	{
		if (hit_plane(ray, t.current_plane, &t.temp_hit)
			&& t.temp_hit.t < t.closest_so_far)
		{
			t.closest_so_far = t.temp_hit.t;
			*hit = t.temp_hit;
			t.hit_anything = 1;
		}
		t.current_plane = t.current_plane->next;
	}
	while (t.current_cylinder)
	{
		t.temp_hit.t = t.closest_so_far;
		if (hit_cylinder(ray, t.current_cylinder, &t.temp_hit)
			&& t.temp_hit.t < t.closest_so_far)
		{
			t.closest_so_far = t.temp_hit.t;
			*hit = t.temp_hit;
			t.hit_anything = 1;
		}
		t.current_cylinder = t.current_cylinder->next;
	}
	return (t.hit_anything);
}
