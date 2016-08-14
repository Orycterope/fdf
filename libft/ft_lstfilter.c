/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfilter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/14 16:54:17 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/14 18:01:40 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfilter(t_list **lst, int (*filter_func)(void*),
		void (*free_func)(void*))
{
	t_list	*previous;
	t_list	*next;
	t_list	*i;

	previous = NULL;
	i = *lst;
	while (i)
	{
		next = i->next;
		if ((*filter_func)((*lst)->content))
		{
			if (previous == NULL)
				*lst = next;
			else
				previous->next = next;
			(*free_func)(i->content);
			free(i);
		}
		else
			previous = i;
		i = next;
	}
}
