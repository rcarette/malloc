/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 16:43:52 by rcarette          #+#    #+#             */
/*   Updated: 2017/11/12 16:17:57 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// PROT_READ | PROT_WRITE 3
// MAP_ANON 4096
// MAP_SHARED = 1;
// MAP_FIXED = 16;
// MAP_FAILED == (void *)-1

#include "malloc.h"

void	*new_allocate(size_t value)
{
	return (mmap(0, value, \
					PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0));
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
		tmp = g_mem.tiny;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = block;
	}
	else if(!g_mem.nbr_tiny)
		g_mem.tiny = block;
	return (block->adress);
}

void	*manage_tiny(size_t size)
{
	t_meta	*blk;
	t_meta	*new_blk;

	blk = g_mem.tiny;
	if (!g_mem.tiny_page)
	{
		g_mem.tiny_page = new_allocate(TINY_MAX_PAGE);
		g_mem.nbr_tiny = 0;
	}
	if ((new_blk = search_block(TINY, size)))
		return (new_blk);
	new_blk = g_mem.tiny_page + (g_mem.nbr_tiny * TINY);
	new_blk->next = NULL;
	new_blk->free = 0x1;
	new_blk->size = size;
	new_blk->adress = g_mem.tiny_page + (g_mem.nbr_tiny * TINY) + sizeof(t_meta) + 1;
	if (!g_mem.tiny)
		g_mem.tiny = new_blk;
	else
	{
		while (blk->next)
			blk = blk->next;
		blk->next = new_blk;
	}
	++g_mem.nbr_tiny;
	if (g_mem.nbr_tiny % 256 == 0)
		g_mem.tiny_page = NULL;
	return (new_blk->adress);
}


void	*manage_small(size_t size)
{

	return (NULL);
}

void	*manage_large(size_t size)
{
	return (NULL);
}

int		init_malloc()
{
	g_mem.tiny = NULL;
	g_mem.tiny = NULL;
	g_mem.small = NULL;
	g_mem.large = NULL;
	g_mem.nbr_tiny= 0x0;
	g_mem.nbr_small= 0x0;
	g_mem.nbr_large= 0x0;
	g_mem.tiny_page = NULL;
	g_mem.small_page = NULL;
	g_mem.tiny_free = NULL;
	g_mem.small_free = NULL;
	g_mem.large_free = NULL;
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
		return (manage_tiny(size));
	else if (size <= (SMALL - sizeof(t_meta)))
		return (manage_small(size));
	else
		return (manage_large(size));
	return (NULL);
}
