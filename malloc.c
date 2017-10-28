/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 16:43:52 by rcarette          #+#    #+#             */
/*   Updated: 2017/10/28 14:46:48 by rcarette         ###   ########.fr       */
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
	/*g_memory_control.tiny_page = mmap(0, TINY_MAX_PAGE, \
					PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);*/
	g_memory_control.small_page = mmap(0, SMALL_MAX_PAGE, \
						PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
}


void	*malloc(size_t size)
{
	if (!size)
		return (NULL);
	else if (!g_memory_control.tiny && !g_memory_control.small && !g_memory_control.large)
		init_malloc();
	int i = 0;
	while (1)
	{
		printf("%c %d\n", ((char *)g_memory_control.small_page)[i], i);
		i++;
	}
	printf("%p\n", g_memory_control.small_page);
	return (NULL);
}

int main(void)
{
	malloc(1);
	return (0);
}
