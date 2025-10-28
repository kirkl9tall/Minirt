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

t_vec3	ray_trace(t_mini *mini, t_ray ray)
{
	t_hit	hit;

	if (find_closest_hit(mini, ray, &hit))
		return (add_light_shadow(mini, hit)); // TODO add light and ambiant
	return ((t_vec3){0, 0, 0});
}

void	my_put_pixel(t_mini *mini, int x, int y, t_vec3 vec3_color)
{
	char	*pixel;
    int color;
	pixel = mini->mlx_utils.addr + (y * mini->mlx_utils.size_line) + (x
			* (mini->mlx_utils.bpp / 8));
    color = 1;//TODO
	*(int *)pixel = color;
}

void	render_scene(t_mini *mini)
{
	int		x;
	int		y;
	t_ray	ray;
	t_vec3	color;

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
