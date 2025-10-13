/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m45kf4c3 </var/spool/mail/m45kf4c3>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 19:08:22 by m45kf4c3          #+#    #+#             */
/*   Updated: 2025/09/27 19:08:22 by m45kf4c3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "../GC/gc.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

size_t	ft_strlen(char *s);
char	*ft_strndup(char *s, size_t len, t_gc **gc);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2, t_gc **gc);
char	*ft_substr(char *s, int start, int len, t_gc **gc);
char	*ft_strdup(char *s, t_gc **gc);
char	*get_next_line(int fd, t_gc **gc);

#endif
