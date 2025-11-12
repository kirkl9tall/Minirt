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
	exit(0);
}

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
