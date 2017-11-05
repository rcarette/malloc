#include "malloc.h"


static void	add_lst_free(t_meta *block)
{
	t_meta	*tmp;

	tmp = NULL;
	if (!g_mem.tiny_free)
		g_mem.tiny_free = block;
	else
	{
		tmp = g_mem.tiny_free;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = block;
	}
}

void		ft_free(void *ptr)
{
	t_meta	*block;
	t_meta	*prev;

	prev = NULL;
	if (g_mem.tiny != NULL)
	{
		block = g_mem.tiny;
		while (block)
		{
			if ((size_t)block->adress == (size_t)ptr)
			{
				if ((size_t)g_mem.tiny  == (size_t)block)
					g_mem.tiny = (g_mem.tiny->next) ? g_mem.tiny->next : NULL;
				else
					prev->next = (block->next != NULL) ? block->next : NULL;
				block->next = NULL;
				add_lst_free(block);
			}
			prev = block;
			block = block->next;
		}
	}
		
}
