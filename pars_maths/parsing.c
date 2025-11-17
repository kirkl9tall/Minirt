/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:45:21 by abismail          #+#    #+#             */
/*   Updated: 2025/11/17 18:30:10 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

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

void	cleaner_exit(void)
{
	printf("error\n");
	gc_clean(get_gc(NULL));
	exit(1);
}

int	count_split(char **splited)
{
	int	i;

	i = 0;
	if (!splited)
		cleaner_exit();
	while (splited[i])
		i++;
	if (*splited[i - 1] == '\n')
		--i;
	return (i);
}

double	atoi_loop(char *nptr, double num)
{
	int		x;
	int		found_dot;
	double	decimal_place;

	x = 0;
	decimal_place = 1;
	found_dot = 0;
	while ((nptr[x] >= '0' && nptr[x] <= '9') || nptr[x] == '.')
	{
		if (nptr[x] == '.')
			found_dot = 1;
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
	return (num);
}

double	ft_atoi_double(char *nptr, double min, double max)
{
	int		x;
	int		signe;
	double	num;

	x = 0;
	signe = 1;
	num = 0;
	while (nptr[x] == '\t' || nptr[x] == ' ' || (nptr[x] >= 9 && nptr[x] <= 13))
		x++;
	if (nptr[x] == '+' || nptr[x] == '-')
	{
		if (nptr[x] == '-')
			signe *= -1;
		x++;
	}
	num = atoi_loop(&nptr[x], num);
	if ((num * signe) < min || (num * signe) > max)
		cleaner_exit();
	return (num * signe);
}
