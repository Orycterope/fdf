/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 16:40:31 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/17 21:14:20 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_conversion.h"
#include "get_conversion_parts.h"

t_conversion	*save_conversion_format(char *str, va_list args)
{
	t_conversion	*conv;
	int				i;

	i = 1;
	if (!(conv = (t_conversion*)malloc(sizeof(t_conversion))))
		return (NULL);
	conv->conversion = 0;
	conv->flags = get_flags(&str[i]);
	i += ft_strlen(conv->flags);
	if (str[i] == '*')
		conv->width = ft_itoa((int)va_arg(args, int));
	else
		conv->width = get_width(&str[i]);
	i += (str[i] == '*') ? 1 : ft_strlen(conv->width);
	if (str[i] == '.' && str[i + 1] == '*')
		conv->precision = ft_strjoin_free(ft_strdup("."),
				ft_itoa((int)va_arg(args, int)));
	else
		conv->precision = get_precision(&str[i]);
	i += (str[i] == '.' && str[i + 1] == '*') ? 2 : ft_strlen(conv->precision);
	conv->modifier = get_modifier(&str[i]);
	i += ft_strlen(conv->modifier);
	conv->conversion = get_conversion(&str[i]);
	conv->length = ++i;
	return (resolve_alias(conv));
}

void			free_conversion_format(t_conversion *conv)
{
	free(conv->flags);
	free(conv->width);
	free(conv->precision);
	free(conv->modifier);
	free(conv);
}
