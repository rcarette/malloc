/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_search_mem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcarette <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 14:15:14 by rcarette          #+#    #+#             */
/*   Updated: 2017/11/01 14:21:46 by rcarette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*search_mem(t_meta *list)
{
	return (list->adress);
}

t_meta			*start_search_mem(enum e_token value)
{
	t_meta	*list = NULL;
	if (IS_TINY(value))
		list = g_mem.disp_tiny;
	else if (IS_SMALL(value))
		list = g_mem.disp_small;
	else
		list = g_mem.disp_large;
	if (!list)
		return (NULL);
	return (search_mem(list));
}
