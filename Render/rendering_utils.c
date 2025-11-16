/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 17:32:16 by zatais            #+#    #+#             */
/*   Updated: 2025/11/16 17:32:16 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	is_in_shadow(t_mini *mini, t_vec3 point, t_vec3 normal, t_vec3 *light_dir)
{
	t_ray	shadow_ray;
	t_hit	shadow_hit;
	double	light_distance;
	t_vec3	to_light;

	to_light = vect_subs(mini->light.light_point, point);
	light_distance = sqrt(vect_prod(to_light, to_light));
	*light_dir = vect_normalized(to_light);
	shadow_ray.origin = point;
	shadow_ray.direction = *light_dir;
	if (find_closest_hit(mini, shadow_ray, &shadow_hit))
		if (shadow_hit.t < light_distance)
			return (1);
	return (0);
}

t_vec3	add_light_shadow(t_mini *mini, t_hit hit)
{
	double	brightness;
	t_vec3	final_color;
	t_vec3	light_dir;
	t_vec3	diffuse;

	final_color.x = mini->amb.color.x * mini->amb.alr * hit.color.x / 255.0;
	final_color.y = mini->amb.color.y * mini->amb.alr * hit.color.y / 255.0;
	final_color.z = mini->amb.color.z * mini->amb.alr * hit.color.z / 255.0;
	if (!is_in_shadow(mini, hit.point, hit.normal, &light_dir))
	{
		brightness = fmax(vect_prod(hit.normal, light_dir), 0);
		diffuse.x = (mini->light.color.x * hit.color.x * brightness
				* mini->light.lbr) / 255;
		diffuse.y = (mini->light.color.y * hit.color.y * brightness
				* mini->light.lbr) / 255;
		diffuse.z = (mini->light.color.z * hit.color.z * brightness
				* mini->light.lbr) / 255;
		final_color.x = fmin(final_color.x + diffuse.x, 255);
		final_color.y = fmin(final_color.y + diffuse.y, 255);
		final_color.z = fmin(final_color.z + diffuse.z, 255);
	}
	return (final_color);
}
