#include "minirt.h"

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

int count_split(char **splited)
{
    int i = 0;

    while (splited[i])
        i++;
    return i;
}

double ft_atoi_double(char *nptr)
{
	int	x;
	int	signe;
	double	num;
    double decimal_place;
    int found_dot;

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
	while (nptr[x] >= '0' && nptr[x] <= '9' || nptr[x] == '.' )
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
	return (num * signe);
}

int assigner(t_mini *mini , char **splited)
{
    if(!ft_strcmp(splited[0],"A"))
    {
        int rgb[3];
        char **splited_comma;
        if (count_split(splited) != 3)
        {
            printf("Error\nInvalid Ambient lighting format\n");
            return 1;
        }
        mini->amb->alr = ft_atoi_double(splited[1]); 
        splited_comma = ft_split(splited[2], ',');
        if (count_split(splited_comma) != 3)
        {
            printf("Error\nInvalid Ambient lighting color format\n");
            return 1;
        }
        int  i = 0;

        while (splited_comma[i])
        {
            rgb[i] = ft_atoi(splited_comma[i]);
            if (rgb[i] < 0 && rgb[i] > 255)
            {
                printf("Error\nInvalid Ambient lighting color format\n");
                return 1; 
            }
            i++;
        }
        mini->amb->color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
    }
    else if (!ft_strcmp(splited[0],"C"))
    {   
        char **splited_comma;
        if (count_split(splited) != 4)
        {
            printf("Error\nInvalid Camera format\n");
            return 1;
        }
        splited_comma = ft_split(splited[1],',');
        mini->cam->pos.x = ft_atoi(splited_comma[0]);
        mini->cam->pos.y = ft_atoi(splited_comma[1]);
        mini->cam->pos.z = ft_atoi(splited_comma[2]);
        splited_comma = ft_split(splited[2],',');
        mini->cam->orient.x = ft_atoi(splited_comma[0]);
        mini->cam->orient.y = ft_atoi(splited_comma[1]);
        mini->cam->orient.z = ft_atoi(splited_comma[2]);
        mini->cam->fov = ft_atoi(splited[3]);
    }
    else if (!ft_strcmp(splited[0],"L"))
    {
        int rgb[3];
        char **splited_comma;
        if (count_split(splited) != 4)
        {
            printf("Error\nInvalid Camera format\n");
            return 1;
        }
        splited_comma = ft_split(splited[1],',');
        mini->light->light_point.x = ft_atoi(splited_comma[0]);
        mini->light->light_point.y = ft_atoi(splited_comma[1]);
        mini->light->light_point.z = ft_atoi(splited_comma[2]);
        mini->light->lbr = ft_atoi_double(splited[2]);
        splited_comma = ft_split(splited[3],',');
        if (count_split(splited_comma) != 3)
        {
            printf("Error\nInvalid Ambient lighting color format\n");
            return 1;
        }
        int  i = 0;
        while (splited_comma[i])
        {
            rgb[i] = ft_atoi(splited_comma[i]);
            if (rgb[i] < 0 && rgb[i] > 255)
            {
                printf("Error\nInvalid Ambient lighting color format\n");
                return 1; 
            }
            i++;
        }
        mini->light->color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
    }
    else  if(!ft_strcmp(splited[0],"pl"))
    {
        int rgb[3];
        char **splited_comma;
        if (count_split(splited) != 4)
        {
            printf("Error\nInvalid Plane format\n");
            return 1;
        }
        splited_comma = ft_split(splited[1],',');
        mini->plane->cor_plan.x = ft_atoi_double(splited_comma[0]);
        mini->plane->cor_plan.y = ft_atoi_double(splited_comma[1]);
        mini->plane->cor_plan.z = ft_atoi_double(splited_comma[2]);
        splited_comma = ft_split(splited[2],',');
        mini->plane->nnv_plan.x = ft_atoi_double(splited_comma[0]);
        mini->plane->nnv_plan.y = ft_atoi_double(splited_comma[1]);
        mini->plane->nnv_plan.z = ft_atoi_double(splited_comma[2]);
        splited_comma = ft_split(splited[3],',');
        if (count_split(splited_comma) != 3)
        {
            printf("Error\nInvalid Ambient lighting color format\n");
            return 1;
        }
        int  i = 0;
        while (splited_comma[i])
        {
            rgb[i] = ft_atoi(splited_comma[i]);
            if (rgb[i] < 0 && rgb[i] > 255)
            {
                printf("Error\nInvalid Ambient lighting color format\n");
                return 1; 
            }
            i++;
        }
        mini->plane->color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
    }
    else if (!ft_strcmp(splited[0],"sp"))
    {
        int rgb[3];
        char **splited_comma;
        if (count_split(splited) != 4)
        {
            printf("Error\nInvalid Plane format\n");
            return 1;
        }
        splited_comma = ft_split(splited[1],',');
        mini->sph->sph_center.x = ft_atoi_double(splited_comma[0]);
        mini->sph->sph_center.y = ft_atoi_double(splited_comma[1]);
        mini->sph->sph_center.z = ft_atoi_double(splited_comma[2]);
        mini->sph->s_diam = ft_atoi_double(splited[2]);
        splited_comma = ft_split(splited[3],',');
        if (count_split(splited_comma) != 3)
        {
            printf("Error\nInvalid Ambient lighting color format\n");
            return 1;
        }
        int  i = 0;
        while (splited_comma[i])
        {
            rgb[i] = ft_atoi(splited_comma[i]);
            if (rgb[i] < 0 && rgb[i] > 255)
            {
                printf("Error\nInvalid Ambient lighting color format\n");
                return 1; 
            }
            i++;
        }
        mini->sph->color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
    }
    else if (!ft_strcmp(splited[0],"cy"))
    {   
        int rgb[3];
        char **splited_comma;
        if (count_split(splited) != 6)
        {
            printf("Error\nInvalid Plane format\n");
            return 1;
        }
        splited_comma = ft_split(splited[1],',');
        mini->cy->cy_center.x = ft_atoi_double(splited_comma[0]);
        mini->cy->cy_center.y = ft_atoi_double(splited_comma[1]);
        mini->cy->cy_center.z = ft_atoi_double(splited_comma[2]);
        splited_comma = ft_split(splited[2],',');
        mini->cy->nv_cy.x = ft_atoi_double(splited_comma[0]);
        mini->cy->nv_cy.y = ft_atoi_double(splited_comma[1]);
        mini->cy->nv_cy.z = ft_atoi_double(splited_comma[2]);
        mini->cy->cy_diam = ft_atoi_double(splited[3]);
        mini->cy->cy_height = ft_atoi_double(splited[4]);
        splited_comma = ft_split(splited[3],',');
        if (count_split(splited_comma) != 3)
        {
            printf("Error\nInvalid Ambient lighting color format\n");
            return 1;
        }
        int  i = 0;
        while (splited_comma[i])
        {
            rgb[i] = ft_atoi(splited_comma[i]);
            if (rgb[i] < 0 && rgb[i] > 255)
            {
                printf("Error\nInvalid Ambient lighting color format\n");
                return 1; 
            }
            i++;
        }
        mini->cy->color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
    }

}
void parsing(int fd,t_mini *mini)
{
    char *content;
    char **splited;
    int i = 0;
    content = get_next_line(fd);

    while (content)
    {
        splited = ft_split(content,' ');
        assigner(mini,splited);
        printf("%s",content);
        free(content);
        content = get_next_line(fd);
    }
}