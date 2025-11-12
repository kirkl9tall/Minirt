/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_maths2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:10:49 by abismail          #+#    #+#             */
/*   Updated: 2025/11/12 14:13:50 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	vect_len(t_vec3 v1)
{
	return (sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z)));
}

t_vec3	vect_normalized(t_vec3 v1)
{
	t_vec3	v;
	double	len;

	len = vect_len(v1);
	if (len < 1e-8)
		return (v1);
	v.x = v1.x / len;
	v.y = v1.y / len;
	v.z = v1.z / len;
	return (v);
}
