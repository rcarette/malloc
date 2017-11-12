#include "malloc.h"

void	show(t_meta *l)
{
	t_meta	*list;

	list = l;
	while (list)
	{
		printf("Taille Octets: %ld\n", list->size);
		printf("Adresse data: %p\n", list->adress);
		printf("Value data: %s\n", list->adress);
		printf("*********************************\n\n");
		list = list->next;
	}	
}

int	main(void)
{
	char	*ptr = ft_malloc(10);
	char	*ptr1 = ft_malloc(25);
	char	*ptr2 = ft_malloc(58);
	show(g_mem.tiny);
	ft_free(ptr);
	ft_free(ptr1);
	ft_free(ptr2);
	ptr = ft_malloc(78);
	ft_malloc(10);
	ft_malloc(21);
	ft_free(ptr);
	ft_malloc(85);
	ft_malloc(88);
	ft_free(ptr2);
	printf("%d\n", g_mem.nbr_tiny);
	printf("\n\n\n\n\n");
	show(g_mem.tiny);
	printf("\n\n\n\n\n");
	show(g_mem.tiny_free);
	return(0);
}
