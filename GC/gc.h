#include <stdlib.h>
#include <unistd.h>

#ifndef GC_H
# define GC_H

typedef struct s_gc
{
	void		*ptr;
	struct s_gc	*next;
}				t_gc;

void			gc_clean(t_gc **gc);
void			gc_add(t_gc **gc, void *ptr);
void			gc_remove(t_gc **gc, void *ptr);
void			*gc_malloc(t_gc **gc, size_t size);
t_gc			**get_gc(t_gc **new_gc);

#endif
