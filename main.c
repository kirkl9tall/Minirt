#include "minirt.h"

int	check_file_mini(char *argv)
{
	int	i;
	int	dot_pos;

	i = 0;
	dot_pos = -1;
	while (argv[i])
	{
		if (argv[i] == '.')
			dot_pos = i;
		i++;
	}
	if (dot_pos == -1 || dot_pos == 0 || argv[dot_pos + 1] != 'r'
		|| argv[dot_pos + 2] != 't' || argv[dot_pos + 3] != '\0')
	{
		write(2, "Error: Invalid .rt file \n", 26);
		return (0);
	}
	return (1);
}

int	init_mini(t_mini *mini, char *title)
{
	mini->mlx_utils.mlx = mlx_init();
	if (!mini->mlx_utils.mlx)
		return (1);
	gc_add(&mini->gc, mini->mlx_utils.mlx);
	mini->mlx_utils.win = mlx_new_window(mini->mlx_utils.mlx, W_W, W_H, title);
	if (!mini->mlx_utils.win)
		return (1);
	gc_add(&mini->gc, mini->mlx_utils.win);
	mini->mlx_utils.img = mlx_new_image(mini->mlx_utils.mlx, W_W, W_H);
	if (!mini->mlx_utils.img)
		return (1);
    gc_add(&mini->gc, mini->mlx_utils.img);
	mini->mlx_utils.addr = mlx_get_data_addr(mini->mlx_utils.img,
												&mini->mlx_utils.bpp,
												&mini->mlx_utils.size_line,
												&mini->mlx_utils.endian);
    if (!mini->mlx_utils.addr)
        return (1);
    gc_add(&mini->gc, mini->mlx_utils.addr);
	return (0);
}
int	close_window(t_mini *mini)
{
    // gc_clean(&mini->gc);
	exit(0);
}

// void	print_scene(t_mini *mini)
// {
// 	t_sphere	*s;
// 	int			i;
// 	t_plan		*p;
// 	t_cylin		*c;

// 	printf("===== DEBUG SCENE =====\n\n");
// 	// Ambient
// 	printf("Ambient:\n");
// 	printf("  ratio = %.2f, color = %d\n\n", mini->amb.alr, mini->amb.color);
// 	// Camera
// 	printf("Camera:\n");
// 	printf("  pos     = (%.2f, %.2f, %.2f)\n", mini->cam.pos.x, mini->cam.pos.y,
// 			mini->cam.pos.z);
// 	printf("  orient  = (%.2f, %.2f, %.2f)\n", mini->cam.orient.x,
// 			mini->cam.orient.y, mini->cam.orient.z);
// 	printf("  up_v    = (%.2f, %.2f, %.2f)\n", mini->cam.up_v.x,
// 			mini->cam.up_v.y, mini->cam.up_v.z);
// 	printf("  right_v = (%.2f, %.2f, %.2f)\n", mini->cam.right_v.x,
// 			mini->cam.right_v.y, mini->cam.right_v.z);
// 	printf("  fov     = %.2f\n", mini->cam.fov);
// 	printf("  canvas  = %.2f x %.2f\n\n", mini->cam.width_canva,
// 			mini->cam.height_canva);
// 	// Light
// 	printf("Light:\n");
// 	printf("  pos   = (%.2f, %.2f, %.2f)\n", mini->light.light_point.x,
// 			mini->light.light_point.y, mini->light.light_point.z);
// 	printf("  ratio = %.2f, color = %d\n\n", mini->light.lbr,
// 			mini->light.color);
// 	// Spheres
// 	s = mini->sph;
// 	i = 0;
// 	while (s)
// 	{
// 		printf("Sphere %d:\n", i++);
// 		printf("  center = (%.2f, %.2f, %.2f)\n", s->sph_center.x,
// 				s->sph_center.y, s->sph_center.z);
// 		printf("  diam   = %.2f, color = %d\n\n", s->s_diam, s->color);
// 		s = s->next;
// 	}
// 	// Planes
// 	p = mini->plane;
// 	i = 0;
// 	while (p)
// 	{
// 		printf("Plane %d:\n", i++);
// 		printf("  point  = (%.2f, %.2f, %.2f)\n", p->cor_plan.x, p->cor_plan.y,
// 				p->cor_plan.z);
// 		printf("  normal = (%.2f, %.2f, %.2f)\n", p->nnv_plan.x, p->nnv_plan.y,
// 				p->nnv_plan.z);
// 		printf("  color  = %d\n\n", p->color);
// 		p = p->next;
// 	}
// 	// Cylinders
// 	c = mini->cy;
// 	i = 0;
// 	while (c)
// 	{
// 		printf("Cylinder %d:\n", i++);
// 		printf("  center = (%.2f, %.2f, %.2f)\n", c->cy_center.x,
// 				c->cy_center.y, c->cy_center.z);
// 		printf("  axis   = (%.2f, %.2f, %.2f)\n", c->nv_cy.x, c->nv_cy.y,
// 				c->nv_cy.z);
// 		printf("  diam   = %.2f, height = %.2f, color = %d\n\n", c->cy_diam,
// 				c->cy_height, c->color);
// 		c = c->next;
// 	}
// 	printf("===== END SCENE =====\n");
// }

int	handle_keypress(int keysym, t_mini *fdf)
{
	if (keysym == XK_Escape)
	{
		// free
		exit(0);
	}
}

int	main(int argc, char *argv[])
{
	t_mini	mini;
	int		fd;

	if (argc == 2)
	{
		if (!check_file_mini(argv[1]))
			return (0);
		ft_memset(&mini, 0, sizeof(t_mini));//TODO ft_memset
		fd = open(argv[1], O_RDONLY);
		parsing(fd, &mini);
		if (init_mini(&mini, "MiniRT"))
			return (gc_clean(&mini.gc), 0);
		project_camera(&mini);
		render_scene(&mini); // TODO
		mlx_hook(mini.mlx_utils.win, 17, 0, close_window, &mini);
		mlx_key_hook(mini.mlx_utils.win, handle_keypress,&mini);
		mlx_loop(mini.mlx_utils.mlx);
	}
}
