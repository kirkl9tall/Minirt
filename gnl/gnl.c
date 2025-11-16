/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abismail <abismail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 16:58:00 by abismail          #+#    #+#             */
/*   Updated: 2025/11/16 17:01:15 by abismail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	if (c == '\0')
		return (&s[i]);
	return (NULL);
}

static char	*extract_line_from_remainder(char **remainder, t_gc **gc)
{
	char	*newline_pos;
	char	*line;
	char	*temp;

	if (!*remainder)
		return (NULL);
	newline_pos = ft_strchr(*remainder, '\n');
	if (newline_pos)
		line = ft_strndup(*remainder, newline_pos - *remainder + 1, gc);
	else
		line = ft_strndup(*remainder, ft_strlen(*remainder), gc);
	if (newline_pos)
	{
		temp = ft_substr(*remainder, newline_pos - *remainder + 1,
				ft_strlen(newline_pos + 1), gc);
		if (!temp)
			return (NULL);
		*remainder = temp;
	}
	else
		*remainder = NULL;
	return (line);
}

int	remainder_update(char **remainder, char *buf, ssize_t r, t_gc **gc)
{
	char	*temp;

	buf[r] = '\0';
	if (*remainder)
	{
		temp = ft_strjoin(*remainder, buf, gc);
		if (!temp)
			return (0);
		*remainder = temp;
	}
	else
	{
		*remainder = ft_strndup(buf, r, gc);
		if (!*remainder)
			return (0);
	}
	return (1);
}

char	*get_next_line(int fd, t_gc **gc)
{
	char		*buf;
	static char	*remainder;
	ssize_t		readed_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = gc_malloc(gc, BUFFER_SIZE + 1);
	while (1)
	{
		if (remainder && ft_strchr(remainder, '\n'))
		{
			return (extract_line_from_remainder(&remainder, gc));
		}
		readed_bytes = read(fd, buf, BUFFER_SIZE);
		if (readed_bytes <= 0)
		{
			if (readed_bytes == 0 && remainder && *remainder)
				return (extract_line_from_remainder(&remainder, gc));
			return (NULL);
		}
		if (!remainder_update(&remainder, buf, readed_bytes, gc))
			return (NULL);
	}
}
