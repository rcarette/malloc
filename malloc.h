/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/28 04:17:04 by rcarette          #+#    #+#             */
/*   Updated: 2017/11/04 13:24:06 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <stdio.h>
#include <string.h>

# define TINY_PAGE 8
# define TINY_MAX_PAGE (TINY_PAGE * 4096)
# define TINY 128

# define SMALL_PAGE 32
# define SMALL_MAX_PAGE (SMALL_PAGE * 4096)
# define SMALL 512

# define IS_TINY(x) (x == T_TINY)
# define IS_SMALL(x) (x == T_SMALL)

enum e_token
{
	FALSE,
	TRUE,
	T_TINY = 128,
	T_SMALL = 512,
	T_LARGE
};

typedef struct		s_meta
{
	int			free; /* Libre || pas libre */
	size_t		size; /* Taille octets */
	struct		s_meta	*next;
	void		*adress;
}					t_meta;


typedef struct	s_mem_control
{
	t_meta		*tiny;
	t_meta		*small;
	t_meta		*large;
	void		*tiny_page;
	void		*small_page;
	int		nbr_tiny;
}				t_mem_control;

t_mem_control g_mem;
void			*ft_malloc(size_t size);
int				init_malloc();
void			*manage_tiny(size_t size);
t_meta			*start_search_mem(enum e_token value);
#endif
