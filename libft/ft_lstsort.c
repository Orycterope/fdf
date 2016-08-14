/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 16:17:58 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/16 17:23:48 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

static t_list	*next_unsorted(t_list *lst, int (*cmp_func)(void*, void*))
{
	while (lst && lst->next)
	{
		if (cmp_func(lst->content, lst->next->content) > 0)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void			ft_lstsort(t_list *lst, int (*cmp_func)(void*, void*))
{
	t_list	*i;

	while ((i = next_unsorted(lst, cmp_func)))
		while (i->next)
		{
			if ((*cmp_func)(i->content, i->next->content) > 0)
			{
				i->content = (void *)(
						(uintptr_t)i->content ^ (uintptr_t)i->next->content);
				i->next->content = (void *)(
						(uintptr_t)i->content ^ (uintptr_t)i->next->content);
				i->content = (void *)(
						(uintptr_t)i->content ^ (uintptr_t)i->next->content);
				i->content_size = i->content_size ^ i->next->content_size;
				i->next->content_size = i->content_size ^ i->next->content_size;
				i->content_size = i->content_size ^ i->next->content_size;
			}
			i = i->next;
		}
}
