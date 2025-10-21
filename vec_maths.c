#include "minirt.h"

t_vec3	vect_addi(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}
t_vec3	vect_subs(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}
t_vec3	vect_multi(t_vec3 v1, double prod)
{
	t_vec3	v;

	v.x = v1.x * prod;
	v.y = v1.y * prod;
	v.z = v1.z * prod;
	return (v);
}

double	vect_prod(t_vec3 v1, t_vec3 v2)
{
	double	v;

	v = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (v);
}

t_vec3	vect_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v;

	v.x = v1.y * v2.z - v1.z * v2.y;
	v.y = v1.z * v2.x - v1.x * v2.z;
	v.z = v1.x * v2.y - v1.y * v2.x;
	return (v);
}
t_vec3	vect_normalized(t_vec3 v1)
{
	t_vec3	v;
	double	len;

	len = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
	v.x = v1.x / len;
	v.y = v1.y / len;
	v.z = v1.z / len;
	return (v);
}
