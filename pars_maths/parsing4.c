/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:02:54 by abismail          #+#    #+#             */
/*   Updated: 2025/11/15 14:16:08 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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
	mini->amb.color = (t_vec3){rgb[0], rgb[1], rgb[2]};
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
	mini->cam.fov = ft_atoi(splited[3]);
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
	mini->light.color = (t_vec3){rgb[0], rgb[1], rgb[2]};
}

void	assign_params_pl(t_plan *plane, char **splited, t_mini *mini,
		char **splited_comma)
{
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
}
