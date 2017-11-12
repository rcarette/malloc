#include "malloc.h"

static void		*transfer(size_t size, t_meta **lst_src, t_meta **lst_dst)
{
	t_meta	*tmp;

	tmp = *lst_src;

	if (!*lst_src)
		return (NULL);
	*lst_src = ((*lst_src)->next) ? (*lst_src)->next : NULL;
	tmp->next = *lst_dst;
	tmp->size = size;
	*lst_dst = tmp;
	return ((*lst_dst)->adress);
}

void	*search_block(enum e_token value, size_t size)
{
	if (value == TINY)
		return(transfer(size, &g_mem.tiny_free, &g_mem.tiny));
	else if (value == SMALL)
		return(transfer(size, &g_mem.small_free, &g_mem.small));
	else
		return(transfer(size, &g_mem.large_free, &g_mem.large));
	return (NULL);
}
