/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 16:43:52 by rcarette          #+#    #+#             */
/*   Updated: 2017/11/01 16:27:48 by rcarette         ###   ########.fr       */
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
	t_meta	*tmp;

	if (!g_mem.nbr_tiny && !g_mem.tiny)
	{
		new_allocate(TINY_MAX_PAGE);
		return(add_block(size));
	}
	tmp = g_mem.tiny_page; // tmp pointe sur la page 'tiny_page'
	while (tmp->next)
	{
		// si on trouve des block free !
		tmp = tmp->next;
	}
	return(add_block(size));
}


void	*ft_malloc(size_t size)
{
	if (!size)
		return (NULL);
	else if (size <= (TINY - sizeof(t_meta)))
	{
		ft_putstr("BLOCK MEMOIRE TINY\n");
		printf("%d\n", size);
		return (manage_tiny(size));
	}
	return (NULL);
}

int main(void)
{
	int	i = 0;
	char	*ptr;
	t_meta *tmp;

	tmp = g_mem.tiny;
	while (i < 256)
	{
		printf("nbr tiny: %d\n", g_mem.nbr_tiny);
		ptr = ft_malloc(i + 1);
		i++;
		sleep(1);
	}
	while (tmp)
	{
		printf("size: %ld\n", tmp->size);
		printf("free: %ld\n", tmp->free);
		printf("%p\n", tmp->adress);
		printf("%ld\n", g_mem.nbr_tiny);
		tmp = tmp->next;
		(!tmp) ? 0 : printf("\n\n");
		sleep(1);

	}
	/*printf("%p\n", g_mem.tiny->adress);
	printf("size: %ld\n", g_mem.tiny->size);
	printf("free: %ld\n", g_mem.tiny->free);
	printf("nbr tiny: %d\n", g_mem.nbr_tiny);*/

	return (0);
}
