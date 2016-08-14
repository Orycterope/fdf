/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 15:02:46 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/20 15:03:09 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappend(t_list **alst, t_list *new)
{
	t_list	*i;

	if (new == NULL)
		return ;
	if (*alst == NULL)
		*alst = new;
	else
	{
		i = *alst;
		while (i->next)
			i = i->next;
		i->next = new;
	}
}
