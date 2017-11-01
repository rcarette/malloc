/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 16:43:52 by rcarette          #+#    #+#             */
/*   Updated: 2017/10/28 15:52:23 by rcarette         ###   ########.fr       */
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

void	init_malloc()
{
	g_mem.tiny_page = mmap(0, TINY_MAX_PAGE, \
					PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	g_mem.small_page = mmap(0, SMALL_MAX_PAGE, \
						PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!g_mem.last_pointer)
	{
		g_mem.size_small = 0;
		g_mem.size_tiny = 0;
	}
}

void	*manage_tiny(size_t size)
{
	t_meta	*meta;
	t_meta	*s;

	meta = (t_meta *)g_mem.tiny_page + g_mem.size_tiny;
	g_mem.tiny = meta;
	meta->size = 0;
	meta->free = 0;
	meta->next = NULL;
	meta->size = size;
	meta->adress = g_mem.tiny_page + sizeof(t_meta) + 1; 
	s = (t_meta *)g_mem.tiny_page + 128 + 1;
	s->size = 17;
	g_mem.size_tiny += 128;
	s->next = NULL;
	s->adress = g_mem.tiny_page + 128 + 1 + sizeof(t_meta) + 1; 
	meta->next = s;
	return (g_mem.tiny->adress);
}



void	*ft_malloc(size_t size)
{
	if (!size)
		return (NULL);
	else if (!g_mem.last_pointer && g_mem.size_tiny == 0)
		init_malloc();
	if (size <= (TINY - sizeof(t_meta)))
		return (manage_tiny(size));
	return (NULL);
}

int main(void)
{
	//printf("%ld\n", sizeof(t_meta));
	char	*ptr, *ptr1;
	ptr = ft_malloc(7);
	t_meta *meta = g_mem.tiny;
	char *m = g_mem.tiny->next->adress;
	while (meta)
	{
		printf("SIZE = %d\n", meta->size);
		printf("Adress = %p\n", meta->adress);
		meta = meta->next;
		printf("------------------\n\n");

	}
	//printf("%s - %p\n", ptr, ptr);
	return (0);
}
