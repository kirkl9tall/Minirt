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
void	*ft_memset(void *s, int c, size_t n)
{
	size_t	x;

	x = 0;
	while (x < n)
	{
		((unsigned char *)s)[x] = (unsigned char)c;
		x++;
	}
	return (s);
}