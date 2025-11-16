/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatais <zatais@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 17:33:11 by zatais            #+#    #+#             */
/*   Updated: 2025/11/16 17:33:11 by zatais           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include "../gc/gc.h"
# include <stdlib.h>
# include <unistd.h>

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
