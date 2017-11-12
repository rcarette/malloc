#include "malloc.h"

static void		*search_pointor(void *ptr, t_meta *tmp)
{
	while (tmp)
	{
		if (!((size_t)ptr ^ (size_t)tmp->adress))
			return (tmp->adress);
		tmp = tmp->next;
	}
	return (NULL);
}

static void		ctrol_memory(void *ptr)
{
	if (search_pointor(ptr, g_mem.tiny_free) || search_pointor(ptr, g_mem.small_free) \
							|| search_pointor(ptr, g_mem.large_free))
	{
		write(1, "Error in program: double free or corruption ", 44);
		printf("%p\n", ptr); // Norme ?
		kill(getpid(), SIGABRT);
	}
}





static void		add_link(t_meta *block, t_meta **lst_dst)
{
	t_meta	*tmp;

	tmp = *lst_dst;
	if (!*lst_dst)
		(*lst_dst) = block;
	else
	{
		block->next = *lst_dst;
		*lst_dst = block;
	}
}

static int		manage_free(void *ptr, t_meta **lst_src, t_meta **lst_dst)
{
	t_meta	*tmp;
	t_meta	*prev;

	prev = NULL;
	tmp = *lst_src;
	while (tmp)
	{
		if ((size_t)ptr == (size_t)tmp->adress)
		{
			if (!prev)
				*lst_src = ((*lst_src)->next) ? (*lst_src)->next : NULL;
			else
				prev->next = (tmp->next != NULL) ? tmp->next : NULL;
			tmp->next = NULL;
			add_link(tmp, lst_dst);
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}

void			ft_free(void *ptr)
{
	t_meta	*tmp;

	tmp = NULL;

	if (!ptr)
		return ;
	ctrol_memory(ptr);
	if (!manage_free(ptr, &g_mem.tiny, &g_mem.tiny_free))
		return ;
	else if (!manage_free(ptr, &g_mem.small, &g_mem.small_free))
		return ;
	else if (!manage_free(ptr, &g_mem.large, &g_mem.large_free))
		return ;
	return ;
}
