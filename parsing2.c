/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:59:27 by abismail          #+#    #+#             */
/*   Updated: 2025/11/12 13:59:28 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	assign_params_cy(t_cylin *cy, char **splited, t_mini *mini,
		char **splited_comma)
{
	if (count_split(splited) != 6)
		error_pinting("Invalid cylinder format\n");
	splited_comma = ft_split(splited[1], ',', &mini->gc);
	cy->cy_center.x = ft_atoi_double(splited_comma[0], INT_MIN, INT_MAX);
	cy->cy_center.y = ft_atoi_double(splited_comma[1], INT_MIN, INT_MAX);
	cy->cy_center.z = ft_atoi_double(splited_comma[2], INT_MIN, INT_MAX);
	splited_comma = ft_split(splited[2], ',', &mini->gc);
	if (count_split(splited_comma) != 3)
		error_pinting("Invalid Ambientlighting color format\n");
	cy->nv_cy.x = ft_atoi_double(splited_comma[0], -1.0, 1.0);
	cy->nv_cy.y = ft_atoi_double(splited_comma[1], -1.0, 1.0);
	cy->nv_cy.z = ft_atoi_double(splited_comma[2], -1.0, 1.0);
	cy->cy_diam = ft_atoi_double(splited[3], INT_MIN, INT_MAX);
	cy->cy_height = ft_atoi_double(splited[4], INT_MIN, INT_MAX);
	cy->next = NULL;
}

void	past_cy(t_mini *mini, t_cylin *cy)
{
	t_cylin	*trav;

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

void	assign_cy(t_mini *mini, char **splited)
{
	t_cylin	*cy;
	int		rgb[3];
	char	**splited_comma;
	int		i;
	t_cylin	*trav;

	i = 0;
	cy = gc_malloc(&mini->gc, sizeof(t_cylin));
	assign_params_cy(cy, splited, mini, splited_comma);
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
	cy->color = (t_vec3){rgb[0], rgb[1], rgb[2]};
	past_cy(mini, cy);
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
		content = get_next_line(fd, &mini->gc);
	}
}
