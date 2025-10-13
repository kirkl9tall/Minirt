#include "minirt.h"

int check_file_mini(char *argv)
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

int  init_mini (t_mini *mini, char * title)
{
    mini->mlx = mlx_init();
    mini->win = mlx_new_window(mini->mlx,W_W,W_H,title);
    if (!mini->mlx)
        return 1;
    if(!mini->win)
        return 1;
    return 0;
}
int	close_window(t_mini *mini)
{
	free(mini);
	exit(0);
}

void print_scene(t_mini *mini)
{
    printf("===== DEBUG SCENE =====\n\n");

    // Ambient
    printf("Ambient:\n");
    printf("  ratio = %.2f, color = %d\n\n", mini->amb.alr, mini->amb.color);

    // Camera
    printf("Camera:\n");
    printf("  pos     = (%.2f, %.2f, %.2f)\n", mini->cam.pos.x, mini->cam.pos.y, mini->cam.pos.z);
    printf("  orient  = (%.2f, %.2f, %.2f)\n", mini->cam.orient.x, mini->cam.orient.y, mini->cam.orient.z);
    printf("  up_v    = (%.2f, %.2f, %.2f)\n", mini->cam.up_v.x, mini->cam.up_v.y, mini->cam.up_v.z);
    printf("  right_v = (%.2f, %.2f, %.2f)\n", mini->cam.right_v.x, mini->cam.right_v.y, mini->cam.right_v.z);
    printf("  fov     = %.2f\n", mini->cam.fov);
    printf("  canvas  = %.2f x %.2f\n\n", mini->cam.width_canva, mini->cam.height_canva);

    // Light
    printf("Light:\n");
    printf("  pos   = (%.2f, %.2f, %.2f)\n", mini->light.light_point.x, mini->light.light_point.y, mini->light.light_point.z);
    printf("  ratio = %.2f, color = %d\n\n", mini->light.lbr, mini->light.color);

    // Spheres
    t_sphere *s = mini->sph;
    int i = 0;
    while (s)
    {
        printf("Sphere %d:\n", i++);
        printf("  center = (%.2f, %.2f, %.2f)\n", s->sph_center.x, s->sph_center.y, s->sph_center.z);
        printf("  diam   = %.2f, color = %d\n\n", s->s_diam, s->color);
        s = s->next;
    }

    // Planes
    t_plan *p = mini->plane;
    i = 0;
    while (p)
    {
        printf("Plane %d:\n", i++);
        printf("  point  = (%.2f, %.2f, %.2f)\n", p->cor_plan.x, p->cor_plan.y, p->cor_plan.z);
        printf("  normal = (%.2f, %.2f, %.2f)\n", p->nnv_plan.x, p->nnv_plan.y, p->nnv_plan.z);
        printf("  color  = %d\n\n", p->color);
        p = p->next;
    }

    // Cylinders
    t_cylin *c = mini->cy;
    i = 0;
    while (c)
    {
        printf("Cylinder %d:\n", i++);
        printf("  center = (%.2f, %.2f, %.2f)\n", c->cy_center.x, c->cy_center.y, c->cy_center.z);
        printf("  axis   = (%.2f, %.2f, %.2f)\n", c->nv_cy.x, c->nv_cy.y, c->nv_cy.z);
        printf("  diam   = %.2f, height = %.2f, color = %d\n\n", c->cy_diam, c->cy_height, c->color);
        c = c->next;
    }

    printf("===== END SCENE =====\n");
}

int main  (int argc, char *argv[])
{
    t_mini *mini;
    t_gc *gc;
    int fd;

    if (argc == 2)
    {
        if(!check_file_mini(argv[1]))
            return 0;
        mini = gc_malloc(&gc, sizeof (t_mini));
        memset(mini , 0 , sizeof(t_mini));
        mini->gc = gc;
        mini->file = ft_strdup(argv[1], &gc);
        fd = open(mini->file,O_RDONLY);
        parsing(fd,mini);
        if(init_mini(mini,"MiniRT"))
            return 0;
        project_camera(mini);
        render_scene(mini);// TODO
        print_scene(mini);
		mlx_hook(mini->win, 17, 0, close_window, mini);
        mlx_loop(mini->mlx); 
    }
}
