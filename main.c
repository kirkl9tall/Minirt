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
		write(2, "Error: Invalid .fdf file \n", 27);
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
        printf ("file is  : %s\n ",mini->file);
        fd = open(mini->file,O_RDONLY);
        printf ("file descis  : %d\n ",fd);
        if(init_mini(mini,"MiniRT"))
        {
            // clean();
            return 0;
        }   
        mlx_loop(mini->mlx); 
    }

}