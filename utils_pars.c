#include "minirt.h"

int	ft_atoi(char *nptr)
{
	int	signe;
	int	num;
	int x = 0;
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
	while (nptr[x] >= '0' && nptr[x] <= '9')
	{
		num = (num * 10);
		num = num + (nptr[x] - 48);
		x++;
	}
	return (num * signe);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1024);
	return (0);
}

int	ft_isdigit(int x)
{
	if (x >= 48 && x <= 57)
		return (2048);
	return (0);
}

char	*ft_strdup(char *s, t_gc **gc)
{
	size_t	len;
	char	*dup;
	size_t	i;

	if (!s)
		return (NULL);
	len = ft_strlen(s) + 1;
	dup = gc_malloc(gc, len);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char *s1, char *s2, t_gc **gc)
{
	size_t	len1;
	size_t	len2;
	char	*res;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = gc_malloc(gc, len1 + len2 + 1);
	i = 0;
	while (*s1)
		res[i++] = *s1++;
	while (*s2)
		res[i++] = *s2++;
	res[i] = '\0';
	return (res);
}

// void	read_file(t_fdf *fdf)
// {
// 	char	*arr;
// 	int		fd;

// 	fd = open(fdf->argv, O_RDONLY);
// 	fdf->line = 0;
// 	arr = get_next_line(fd);
// 	while (arr)
// 	{
// 		free(arr);
// 		arr = get_next_line(fd);
// 		fdf->line++;
// 	}
// 	free(arr);
// 	fdf->height = fdf->line;
// 	close(fd);
// 	return ;
// }
