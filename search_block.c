#include "malloc.h"

static void	*transfer_tiny(size_t size)
{

	t_meta	*tmp;
	t_meta	*tmp_tiny;

	if (!g_mem.tiny_free)
		return (NULL);
	tmp = g_mem.tiny_free;
	tmp_tiny = g_mem.tiny;
	tmp->next = NULL;
	tmp->size = size;
	g_mem.tiny_free = (g_mem.tiny_free->next) ? g_mem.tiny_free->next : NULL;
	if (!tmp_tiny)
		g_mem.tiny = tmp;
	tmp->next = g_mem.tiny;
	g_mem.tiny = tmp;
	return (g_mem.tiny->adress);
}

void	*search_block(enum e_token value, size_t size)
{
	if (value == TINY)
		return(transfer_tiny(size));
	else if (value == SMALL)
	{

	}
	else
	{
	
	}
	return (NULL);
}
