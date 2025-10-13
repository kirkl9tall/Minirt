#include "gc.h"


t_gc	**get_gc(t_gc **new_gc)
{
    static t_gc	**gc_ptr = NULL;
	
	if (new_gc)
		gc_ptr = new_gc;
	return (gc_ptr);
}

void	gc_clean(t_gc **gc)
{
	t_gc	*current;
	t_gc	*next;

	current = *gc;
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	*gc = NULL;
}

void	gc_add(t_gc **gc, void *ptr)
{
	t_gc	*node;

	node = malloc(sizeof(t_gc));
	if (!node)
	{
		write(2, "gc_add malloc failed\n", 21);
		gc_clean(gc);
		exit(1);
	}
	node->ptr = ptr;
	node->next = *gc;
	*gc = node;
}

void	gc_remove(t_gc **gc, void *ptr)
{
	t_gc	*current;
	t_gc	*prev;

	current = *gc;
	prev = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				*gc = current->next;
			free(current->ptr);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	*gc_malloc(t_gc **gc, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		write(2, "gc_malloc failed\n", 17);
		gc_clean(gc);
		exit(1);
	}
	gc_add(gc, ptr);
	return (ptr);
}
