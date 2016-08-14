/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 22:32:18 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/17 13:10:13 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next;
	t_list	*maillon;

	if (alst == NULL)
		return ;
	maillon = *alst;
	while (maillon)
	{
		next = maillon->next;
		if (del != NULL)
			(*del)(maillon->content, sizeof(t_list));
		free(maillon);
		maillon = next;
	}
	*alst = NULL;
	alst = NULL;
}
