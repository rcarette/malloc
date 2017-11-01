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
		g_mem.size_large = 0;
		g_mem.disp_tiny = NULL;
		g_mem.disp_small = NULL;
		g_mem.disp_large = NULL;
	}
}

void	*new_block(size_t size)
{
	t_meta	*block;

	/*CHECK LA PAGE TINY SI IL Y A ENCORE DE LA PLACE POUR STOCKER LES STRUCTURES*/
	printf("fr\n");
	if (!g_mem.size_tiny)
		block = (t_meta *)g_mem.tiny_page + g_mem.size_tiny;
	else
		block = (t_meta *)g_mem.tiny_page + g_mem.size_tiny + 1;
	printf("te\n");
	//printf("%p\n", g_mem.tiny_page + g_mem.size_tiny + sizeof(t_meta) + 1);
	printf("gfdfe\n");
	block->free = 1;
	printf("ffrfr\n");
	block->size = size;
	block->next = NULL;
	printf("re\n");
	block->adress = g_mem.tiny_page + g_mem.size_tiny + sizeof(t_meta) + 1;
	g_mem.size_tiny += TINY;
	printf("ri\n");
	if (g_mem.size_tiny == TINY * 256)
	{
		g_mem.size_tiny = 0x0;
		ft_putstr("NEW_ MAP");
	}
	return (block->adress);
}

void	*manage_tiny(size_t size)
{
	void	*adress;

	if ((adress = start_search_mem(T_TINY)))
		return (adress);
	return (new_block(size));
}



void	*ft_malloc(size_t size)
{
	if (!size)
		return (NULL);
	else if (!g_mem.size_tiny)
		init_malloc();
	if (size <= (TINY - sizeof(t_meta)))
		return (manage_tiny(size));
	return (NULL);
}

int main(void)
{
	//printf("%ld\n", sizeof(t_meta));
	char	*ptr, *ptr1;
	int		i = 0;
		printf("0\n");
	while (i < 99)
	{
		ptr = ft_malloc(7);
		strcpy(ptr, "Romain");
		printf("%p\n", ptr);
		printf("ju\n");
		printf("%s\n", ptr);
		printf("toto\n");
		printf("%ld\n", g_mem.size_tiny);
		printf("titi\n");
		printf("i = %d\n", i);
		printf("\n");
		i++;
	}
	/*ptr = ft_malloc(7);
	printf("%ld\n", g_mem.size_tiny);
	printf("%p\n", ptr);
	printf("\n");
	ptr = ft_malloc(7);
	printf("%ld\n", g_mem.size_tiny);
	printf("%p\n", ptr);
	printf("\n");
	ptr = ft_malloc(7);
	printf("%ld\n", g_mem.size_tiny);
	printf("%p\n", ptr);
	printf("\n");
	ptr = ft_malloc(7);
	ptr = ft_malloc(7);
	ptr = ft_malloc(7);
	ptr = ft_malloc(7);*/
	return (0);
}
