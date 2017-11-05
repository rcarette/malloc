#include "malloc.h"

static void	*transfer(void)
{
	t_meta	*block;
	t_meta	*tmp;
	
	block = g_mem.tiny_free;
	if (!g_mem.tiny_free->next)
		g_mem.tiny_free = NULL;
	else
		g_mem.tiny_free = g_mem.tiny_free->next;
	
	tmp = g_mem.tiny;
	if (!tmp)
		tmp = block;
	else
	{
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = block;
	}
	return (block->adress);
}

void	*search_block(enum e_token value)
{
	if (value == TINY)
	{
		if (!g_mem.tiny_free)
			return (NULL);
		else
			return (transfer());
	}
}
