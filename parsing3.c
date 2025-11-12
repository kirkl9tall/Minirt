/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:02:22 by abismail          #+#    #+#             */
/*   Updated: 2025/11/12 14:04:52 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	past_pl(t_mini *mini, t_plan *plane)
{
	t_plan	*trav;

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

void	assign_pl(t_mini *mini, char **splited)
{
	t_plan	*plane;
	int		rgb[3];
	char	**splited_comma;
	int		i;
	t_plan	*trav;

	plane = gc_malloc(&mini->gc, sizeof(t_plan));
	assign_params_pl(plane, splited, mini, splited_comma);
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
	plane->color = (t_vec3){rgb[0], rgb[1], rgb[2]};
	past_pl(mini, plane);
}

void	assign_params_sph(t_sphere *sph, char **splited, t_mini *mini,
		char **splited_comma)
{
	if (count_split(splited) != 4)
		error_pinting("Invalid sphere format\n");
	splited_comma = ft_split(splited[1], ',', &mini->gc);
	sph->sph_center.x = ft_atoi_double(splited_comma[0], INT_MIN, INT_MAX);
	sph->sph_center.y = ft_atoi_double(splited_comma[1], INT_MIN, INT_MAX);
	sph->sph_center.z = ft_atoi_double(splited_comma[2], INT_MIN, INT_MAX);
	sph->s_diam = ft_atoi_double(splited[2], INT_MIN, INT_MAX);
	sph->next = NULL;
}

void	past_sph(t_mini *mini, t_sphere *sph)
{
	t_sphere	*trav;

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

void	assign_sph(t_mini *mini, char **splited)
{
	t_sphere	*sph;
	int			rgb[3];
	char		**splited_comma;
	int			i;
	t_sphere	*trav;

	i = 0;
	sph = gc_malloc(&mini->gc, sizeof(t_sphere));
	assign_params_sph(sph, splited, mini, splited_comma);
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
	sph->color = (t_vec3){rgb[0], rgb[1], rgb[2]};
	past_sph(mini, sph);
}
