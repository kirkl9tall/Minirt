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

void    print_scene(t_mini *mini)
{
    int i = 0;

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
    if (mini->sph)
    {
        i = 0;
        while (mini->sph[i].s_diam != 0) // stop condition depends on how you allocate!
        {
            printf("Sphere %d:\n", i);
            printf("  center = (%.2f, %.2f, %.2f)\n", mini->sph[i].sph_center.x, mini->sph[i].sph_center.y, mini->sph[i].sph_center.z);
            printf("  diam   = %.2f, color = %d\n\n", mini->sph[i].s_diam, mini->sph[i].color);
            i++;
        }
    }

    // Planes
    if (mini->plane)
    {
        i = 0;
        while (mini->plane[i].color != 0) // same remark, depends on parsing logic
        {
            printf("Plane %d:\n", i);
            printf("  point  = (%.2f, %.2f, %.2f)\n", mini->plane[i].cor_plan.x, mini->plane[i].cor_plan.y, mini->plane[i].cor_plan.z);
            printf("  normal = (%.2f, %.2f, %.2f)\n", mini->plane[i].nnv_plan.x, mini->plane[i].nnv_plan.y, mini->plane[i].nnv_plan.z);
            printf("  color  = %d\n\n", mini->plane[i].color);
            i++;
        }
    }

    // Cylinders
    if (mini->cy)
    {
        i = 0;
        while (mini->cy[i].cy_diam != 0) // stop condition to adapt
        {
            printf("Cylinder %d:\n", i);
            printf("  center = (%.2f, %.2f, %.2f)\n", mini->cy[i].cy_center.x, mini->cy[i].cy_center.y, mini->cy[i].cy_center.z);
            printf("  axis   = (%.2f, %.2f, %.2f)\n", mini->cy[i].nv_cy.x, mini->cy[i].nv_cy.y, mini->cy[i].nv_cy.z);
            printf("  diam   = %.2f, height = %.2f, color = %d\n\n", mini->cy[i].cy_diam, mini->cy[i].cy_height, mini->cy[i].color);
            i++;
        }
    }

    printf("===== END SCENE =====\n");
}

int main  (int argc, char *argv[])
{
    t_mini *mini;
    int fd;

    if (argc == 2)
    {
        if(!check_file_mini(argv[1]))
            return 0;
        mini = malloc(sizeof (t_mini));
        mini->file = ft_strdup(argv[1]);
        fd = open(mini->file,O_RDONLY);
        if(init_mini(mini,"MiniRT"))
            return 0;
        parsing(fd,mini);
        project_camera(mini);
        print_scene(mini);
		mlx_hook(mini->win, 17, 0, close_window, mini);
        mlx_loop(mini->mlx); 
    }
}