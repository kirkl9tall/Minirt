#include "minirt.h"

void	cleaner_exit(void);

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	x;

	x = 0;
	while ((s1[x] || s2[x]))
	{
		if ((unsigned char)s1[x] != (unsigned char)s2[x])
			return ((unsigned char)s1[x] - (unsigned char)s2[x]);
		x++;
	}
	return (0);
}

int	count_split(char **splited)
{
	int	i;

	i = 0;
	if (!splited)
		cleaner_exit();
	while (splited[i])
		i++;
	return (i);
}

void	cleaner_exit(void)
{
	printf("error error error\n");
	exit(1);
}

double	ft_atoi_double(char *nptr, double min, double max)
{
	int		x;
	int		signe;
	double	num;
	double	decimal_place;
	int		found_dot;

	decimal_place = 1;
	found_dot = 0;
	x = 0;
	signe = 1;
	num = 0;
	while (nptr[x] == '\t' || nptr[x] == ' ' || (nptr[x] >= 9 && nptr[x] <= 13))
		x++;
	if (nptr[x] == '+' || nptr[x] == '-')
	{
		if (nptr[x] == '-')
		{
			signe *= -1;
		}
		x++;
	}
	while ((nptr[x] >= '0' && nptr[x] <= '9') || nptr[x] == '.')
	{
		if (nptr[x] == '.')
		{
			found_dot = 1;
		}
		else
		{
			if (!found_dot)
				num = num * 10 + (nptr[x] - '0');
			else
			{
				decimal_place *= 10;
				num = num + (nptr[x] - '0') / decimal_place;
			}
		}
		x++;
	}
	if ((num * signe) < min || (num * signe) > max)
	{
		// printf(" num is : %lf ",(num * signe));
		cleaner_exit();
	}
	return (num * signe);
}

void	error_pinting(char *error)
{
	printf("Error\n%s\n", error);
}

void	assign_a(t_mini *mini, char **splited)
{
	int		rgb[3];
	char	**splited_comma;
	int		i;

	i = 0;
	if (count_split(splited) != 3)
		error_pinting("Invalid Ambient lighting format\n");
	mini->amb.alr = ft_atoi_double(splited[1], 0.0, 1.0);
	splited_comma = ft_split(splited[2], ',', &mini->gc);
	if (count_split(splited_comma) != 3)
		error_pinting("Invalid Ambient lighting color format\n");
	while (splited_comma[i])
	{
		rgb[i] = ft_atoi(splited_comma[i]);
		if (rgb[i] < 0 && rgb[i] > 255)
			error_pinting("Invalid Ambient lighting color format\n");
		i++;
	}
	mini->amb.color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
}

void	assign_c(t_mini *mini, char **splited)
{
	char	**splited_comma;

	if (count_split(splited) != 4)
		error_pinting("Invalid Camera format\n");
	splited_comma = ft_split(splited[1], ',', &mini->gc);
	mini->cam.pos.x = ft_atoi(splited_comma[0]);
	mini->cam.pos.y = ft_atoi(splited_comma[1]);
	mini->cam.pos.z = ft_atoi(splited_comma[2]);
	splited_comma = ft_split(splited[2], ',', &mini->gc);
	mini->cam.orient.x = ft_atoi(splited_comma[0]);
	mini->cam.orient.y = ft_atoi(splited_comma[1]);
	mini->cam.orient.z = ft_atoi(splited_comma[2]);
	mini->cam.fov = ft_atoi(splited[3]); // must be 0-180;
}

void	assign_l(t_mini *mini, char **splited)
{
	int		rgb[3];
	char	**splited_comma;
	int		i;

	if (count_split(splited) != 4)
		error_pinting("Invalid Camera format\n");
	splited_comma = ft_split(splited[1], ',', &mini->gc);
	mini->light.light_point.x = ft_atoi(splited_comma[0]);
	mini->light.light_point.y = ft_atoi(splited_comma[1]);
	mini->light.light_point.z = ft_atoi(splited_comma[2]);
	mini->light.lbr = ft_atoi_double(splited[2], 0.0, 1.0);
	splited_comma = ft_split(splited[3], ',', &mini->gc);
	if (count_split(splited_comma) != 3)
		error_pinting("Invalid Ambient lighting color format\n");
	i = 0;
	while (splited_comma[i])
	{
		rgb[i] = ft_atoi(splited_comma[i]);
		if (rgb[i] < 0 && rgb[i] > 255)
			error_pinting("Invalid Ambient lighting color format\n");
		i++;
	}
	mini->light.color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
}

void	assign_pl(t_mini *mini, char **splited)
{
	t_plan	*plane;
	int		rgb[3];
	char	**splited_comma;
	int		i;
	t_plan	*trav;

	plane = gc_malloc(&mini->gc, sizeof(t_plan));
	if (count_split(splited) != 4)
		error_pinting("Invalid Plane format\n");
	splited_comma = ft_split(splited[1], ',', &mini->gc);
	plane->cor_plan.x = ft_atoi_double(splited_comma[0], INT_MIN, INT_MAX);
	plane->cor_plan.y = ft_atoi_double(splited_comma[1], INT_MIN, INT_MAX);
	plane->cor_plan.z = ft_atoi_double(splited_comma[2], INT_MIN, INT_MAX);
	splited_comma = ft_split(splited[2], ',', &mini->gc);
	plane->nnv_plan.x = ft_atoi_double(splited_comma[0], 0.0, 1.0);
	plane->nnv_plan.y = ft_atoi_double(splited_comma[1], 0.0, 1.0);
	plane->nnv_plan.z = ft_atoi_double(splited_comma[2], 0.0, 1.0);
	plane->next = NULL;
	splited_comma = ft_split(splited[3], ',', &mini->gc);
	if (count_split(splited_comma) != 3)
		error_pinting("Invalid Ambient lighting color format\n");
	i = 0;
	while (splited_comma[i])
	{
		rgb[i] = ft_atoi(splited_comma[i]);
		if (rgb[i] < 0 && rgb[i] > 255)
			error_pinting("Invalid Ambient lighting color format\n");
		i++;
	}
	plane->color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	if (!mini->plane)
		mini->plane = plane;
	else
	{
		trav = mini->plane;
		while (trav->next)
			trav = trav->next;
		trav->next = plane;
	}
}
void	assign_sph(t_mini *mini, char **splited)
{
	t_sphere	*sph;
	int			rgb[3];
	char		**splited_comma;
	int			i;
	t_sphere	*trav;

	i = 0;
	sph = gc_malloc(&mini->gc, sizeof(t_sphere));
	if (count_split(splited) != 4)
		error_pinting("Invalid Plane format\n");
	splited_comma = ft_split(splited[1], ',', &mini->gc);
	sph->sph_center.x = ft_atoi_double(splited_comma[0], INT_MIN, INT_MAX);
	sph->sph_center.y = ft_atoi_double(splited_comma[1], INT_MIN, INT_MAX);
	sph->sph_center.z = ft_atoi_double(splited_comma[2], INT_MIN, INT_MAX);
	sph->s_diam = ft_atoi_double(splited[2], INT_MIN, INT_MAX);
	sph->next = NULL;
	splited_comma = ft_split(splited[3], ',', &mini->gc);
	if (count_split(splited_comma) != 3)
		error_pinting("Invalid Ambient lighting color format\n");
	while (splited_comma[i])
	{
		rgb[i] = ft_atoi(splited_comma[i]);
		if (rgb[i] < 0 && rgb[i] > 255)
			error_pinting("Invalid Ambient lighting color format\n");
		i++;
	}
	sph->color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	if (!mini->sph)
		mini->sph = sph;
	else
	{
		trav = mini->sph;
		while (trav->next)
			trav = trav->next;
		trav->next = sph;
	}
}

void	assign_cy(t_mini *mini, char **splited)
{
	t_cylin	*cy;
	int		rgb[3];
	char	**splited_comma;
	int		i;
	t_cylin	*trav;

	i = 0;
	cy = gc_malloc(&mini->gc, sizeof(t_cylin));
	if (count_split(splited) != 6)
		error_pinting("Invalid Plane format\n");
	splited_comma = ft_split(splited[1], ',', &mini->gc);
	cy->cy_center.x = ft_atoi_double(splited_comma[0], INT_MIN, INT_MAX);
	cy->cy_center.y = ft_atoi_double(splited_comma[1], INT_MIN, INT_MAX);
	cy->cy_center.z = ft_atoi_double(splited_comma[2], INT_MIN, INT_MAX);
	splited_comma = ft_split(splited[2], ',', &mini->gc);
	if (count_split(splited_comma) != 3)
		error_pinting("Invalid Ambientlighting color format\n");
	cy->nv_cy.x = ft_atoi_double(splited_comma[0], 0.0, 1.0);
	cy->nv_cy.y = ft_atoi_double(splited_comma[1], 0.0, 1.0);
	cy->nv_cy.z = ft_atoi_double(splited_comma[2], 0.0, 1.0);
	cy->cy_diam = ft_atoi_double(splited[3], INT_MIN, INT_MAX);
	cy->cy_height = ft_atoi_double(splited[4], INT_MIN, INT_MAX);
	cy->next = NULL;
	splited_comma = ft_split(splited[5], ',', &mini->gc);
	if (count_split(splited_comma) != 3)
		error_pinting("Invalid Ambientlighting color format\n");
	while (splited_comma[i])
	{
		rgb[i] = ft_atoi(splited_comma[i]);
		if (rgb[i] < 0 && rgb[i] > 255)
			error_pinting("Invalid Ambient lighting color format\n");
		i++;
	}
	cy->color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	if (!mini->cy)
		mini->cy = cy;
	else
	{
		trav = mini->cy;
		while (trav->next)
			trav = trav->next;
		trav->next = cy;
	}
}

void	assigner(t_mini *mini, char **splited)
{
	if (!ft_strcmp(splited[0], "A"))
		assign_a(mini, splited);
	else if (!ft_strcmp(splited[0], "C"))
		assign_c(mini, splited);
	if (!ft_strcmp(splited[0], "L"))
		assign_l(mini, splited);
	else if (!ft_strcmp(splited[0], "pl"))
		assign_pl(mini, splited);
	else if (!ft_strcmp(splited[0], "sp"))
		assign_sph(mini, splited);
	else if (!ft_strcmp(splited[0], "cy"))
		assign_cy(mini, splited);
}
void	parsing(int fd, t_mini *mini)
{
	char	*content;
	char	**splited;

	content = get_next_line(fd, &mini->gc);
	while (content)
	{
		splited = ft_split(content, ' ', &mini->gc);
		assigner(mini, splited);
		// printf("%s",content);
		free(content);
		content = get_next_line(fd, &mini->gc);
	}
}
