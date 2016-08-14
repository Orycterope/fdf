/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 21:49:13 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/17 12:41:42 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list				*ft_lstnew_nocpy(void *content, size_t content_size)
{
	t_list	*lst;

	lst = (t_list*)malloc(sizeof(t_list));
	if (lst == NULL)
		return (NULL);
	lst->next = NULL;
	if (content == NULL)
	{
		lst->content = NULL;
		lst->content_size = 0;
		return (lst);
	}
	lst->content = content;
	lst->content_size = content_size;
	return (lst);
}
