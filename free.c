#include "malloc.h"

static void	add_link(t_meta *block, t_meta *lst_dst)
{
}

static void	*search_pointor(void *ptr, t_meta *tmp)
{
	while (tmp)
	{
		if (!((size_t)ptr ^ (size_t)tmp->adress))
		{
			printf("%p - %p\n", ptr, tmp->adress);
			printf("TROUVER \n");
			sleep(5);
			return (tmp->adress);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static void	ctrol_memory(void *ptr)
{
	if (search_pointor(ptr, g_mem.tiny_free) || search_pointor(ptr, g_mem.small_free) \
							|| search_pointor(ptr, g_mem.large_free))
	{
		write(1, "Error in program: double free or corruption ", 44);
		printf("%p\n", ptr); // Norme ?
		kill(getpid(), SIGABRT);
	}
}

static int	manage_free(void *ptr, t_meta **lst_src, t_meta **lst_dst)
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
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (1);
}

void		ft_free(void *ptr)
{
	t_meta	*tmp;

	tmp = NULL;
	if (!ptr) // SI LE PARAMTER RECU EST NULL 
		return ;
	ctrol_memory(ptr); // CETTE FONCTION PEUT STOPPER LE PROGRAMME SI JAMAIS LE PTR RECU EN PARAMETRE A DEJA ETAIT FREE !!!
	if (!manage_free(ptr, &g_mem.tiny, &g_mem.tiny_free))
		return ;
	/*t_meta	*block;
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
	}*/
		
}
