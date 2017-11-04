/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 16:43:52 by rcarette          #+#    #+#             */
/*   Updated: 2017/11/04 13:28:38 by rcarette         ###   ########.fr       */
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
	if (g_mem.nbr_tiny > 96 + 1)
		g_mem.nbr_tiny = 0;
	return (block->adress);
}

void	*manage_tiny(size_t size)
{
	return(NULL);
}

int		init_malloc()
{
	write(1, "DEBUG: INIT_MALLOC...\n", 22);
	/*
	 * initialize les variables ci-dessous VALEUR (NULL)
	 */
	g_mem.tiny = NULL;
	g_mem.small = NULL;
	g_mem.large = NULL;
	g_mem.nbr_tiny= 0x0;
	return (1);
}


void	*ft_malloc(size_t size)
{
	static int	init = 0;

	if (!size)
		return (NULL);
	else if (!init)
		init += init_malloc();
	else if (size <= (TINY - sizeof(t_meta)))
	{
		ft_putstr("BLOCK MEMOIRE TINY\n");
		return (manage_tiny(size));
	}
	return (NULL);
}

int main(void)
{
	ft_malloc(7);
	ft_malloc(8);
	return (0);
}
