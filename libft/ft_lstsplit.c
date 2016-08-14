/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 12:34:03 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/19 12:42:24 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Splits a list everytime the cmp function returns a non-zero value
** and returns a list of all the sublists created.
** The list is splitted after the element on which cmp_func returned true
*/

t_list			*ft_lstsplit(t_list *lst, int (*cmp_func)(t_list *))
{
	t_list	*parent_lst;
	t_list	*next;

	if (lst == NULL)
		return (NULL);
	parent_lst = NULL;
	ft_lstappend(&parent_lst, ft_lstnew_nocpy(lst, sizeof(void*)));
	while (lst)
	{
		next = lst->next;
		if ((*cmp_func)(lst))
		{
			ft_lstappend(&parent_lst,
				ft_lstnew_nocpy(lst, sizeof(void*)));
			lst->next = NULL;
		}
		lst = next;
	}
	return (parent_lst);
}
