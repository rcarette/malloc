/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/28 04:17:04 by rcarette          #+#    #+#             */
/*   Updated: 2017/10/28 15:41:19 by rcarette         ###   ########.fr       */
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

typedef struct		s_meta
{
	int		free; /* Libre || pas libre */
	size_t		size; /* Taille octets */
	struct s_meta	*next;
	void		*adress;
}			t_meta;


typedef struct		s_mem_control
{
	t_meta		*tiny;
	t_meta		*small;
	t_meta		*large;
	void		*tiny_page;
	void		*small_page;
	int		size_small;
	int		size_tiny;
	t_meta		*last_pointer;
}			t_mem_control;

t_mem_control g_mem;
void	*malloc(size_t size);
void	init_malloc();
void	*manage_tiny(size_t size);
#endif
