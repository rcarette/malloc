#include "malloc.h"

static void	*transfer(enum e_token value, size_t size)
{
	t_meta	*block;
	t_meta	*tmp;

	if (value == TINY)
		block = g_mem.tiny_free;
	g_mem.tiny_free = (g_mem.tiny_free->next) ? g_mem.tiny_free->next : NULL;
	block->next = NULL;
	block->size = size;
	tmp = g_mem.tiny;
	if (!g_mem.tiny)
		g_mem.tiny = block;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = block;
	}
	return (block->adress);
}

void	*search_block(enum e_token value, size_t size)
{
	if (value == TINY && g_mem.tiny_free)
		return (transfer(TINY, size));
	return (NULL);
}
