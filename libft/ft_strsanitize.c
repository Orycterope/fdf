/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsanitize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 14:43:26 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/26 17:34:35 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline int	is_removable_char(char c)
{
	return (c == ' ' || c == '\t' || c == '\0');
}

static int			get_sanitized_size(char *str)
{
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i])
	{
		if (!is_removable_char(str[i]) ||
				(is_removable_char(str[i]) && !is_removable_char(str[i + 1])))
			size++;
		i++;
	}
	return (size);
}

char				*ft_strsanitize(char *str)
{
	char	*new;
	int		size;
	int		i;

	if (str == NULL || (size = get_sanitized_size(str)) == 0)
		return (NULL);
	new = (char *)malloc(size + 1);
	if (new == NULL)
		return (NULL);
	while (str[0] == ' ' || str[0] == '\t')
		str++;
	i = 0;
	while (i < size)
	{
		if (!is_removable_char(str[0]) ||
				(is_removable_char(str[0]) && !is_removable_char(str[1])))
			new[i++] = (is_removable_char(str[0])) ? ' ' : str[0];
		str++;
	}
	new[i] = '\0';
	if (new[size] == ' ')
		new[size] = '\0';
	return (new);
}
