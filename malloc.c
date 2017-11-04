/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 16:43:52 by rcarette          #+#    #+#             */
/*   Updated: 2017/11/04 14:36:24 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// PROT_READ | PROT_WRITE 3
// MAP_ANON 4096
// MAP_SHARED = 1;
// MAP_FIXED = 16;
// MAP_FAILED == (void *)-1

#include "malloc.h"

void	ft_putstr(char *str)
{
	write(1, str, strlen(str));
}

void	new_allocate(enum e_token value)
{
	ft_putstr("toto\n");
	g_mem.tiny_page = mmap(0, value, \
					PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
}

static void	*add_block(size_t size)
{
	t_meta	*block;
	t_meta	*tmp;

	block = g_mem.tiny_page + (g_mem.nbr_tiny * 128);
	block->next = NULL;
	block->free = TRUE;
	block->size = size;
	block->adress = g_mem.tiny_page +
			(g_mem.nbr_tiny * 128) + sizeof(t_meta) + 1;
	if (g_mem.tiny->next != NULL)
	{
		ft_putstr("***CHAINAGE***\n");
		tmp = g_mem.tiny;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = block;
	}
	else if(!g_mem.nbr_tiny)
		g_mem.tiny = block;
	++g_mem.nbr_tiny;
	return (block->adress);
}

void	*manage_tiny(size_t size)
{
	t_meta	*blk;
	t_meta	*new_blk;

	blk = g_mem.tiny;
	if (!g_mem.tiny_page)
	{
		ft_putstr("Manage tiny: g_mem.tiny_page == NULL\n");
		g_mem.tiny_page = mmap(0, TINY_MAX_PAGE, \
						PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
		g_mem.nbr_tiny = 0;
	}
	new_blk = (t_meta *)g_mem.tiny_page + (g_mem.nbr_tiny * TINY);
	new_blk->next = NULL;
	new_blk->free = 0x1;
	new_blk->size = size;
	new_blk->adress = g_mem.tiny_page + (g_mem.nbr_tiny * TINY) + sizeof(t_meta) + 1;
	if (!g_mem.tiny)
		g_mem.tiny = new_blk;
	else
	{
		ft_putstr("CHAINAGE\n");
		while (blk->next)
			blk = blk->next;
		blk->next = new_blk;
	}
	++g_mem.nbr_tiny; // + 1 TINY CREAT BLOCK ;*/
	return (new_blk->adress);
}

int		init_malloc()
{
	/*
	 * initialize les variables ci-dessous VALEUR (NULL)
	 *
	 */
	g_mem.tiny = NULL;
	write(1, "DEBUG: INIT_MALLOC...\n", 22);
	g_mem.tiny = NULL;
	g_mem.small = NULL;
	g_mem.large = NULL;
	g_mem.nbr_tiny= 0x0;
	g_mem.tiny_page = NULL;
	g_mem.small_page = NULL;
	return (1);
}


void	*ft_malloc(size_t size)
{
	static int	init = 0;

	if (!size)
		return (NULL);
	else if (!init)
		init += init_malloc();
	if (size <= (TINY - sizeof(t_meta)))
	{
		ft_putstr("BLOCK MEMOIRE TINY\n");
		return (manage_tiny(size));
	}
	return (NULL);
}

int main(void)
{
	char *ptr = ft_malloc(7);
	char *ptr1 = ft_malloc(14);
	char *ptr2 = ft_malloc(60);
	while (g_mem.tiny)
	{
		printf("Size: %ld\n", g_mem.tiny->size);
		g_mem.tiny = g_mem.tiny->next;
	}
	return (0);
}
