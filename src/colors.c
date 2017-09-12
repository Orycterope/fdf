/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 15:45:31 by tvermeil          #+#    #+#             */
/*   Updated: 2017/09/12 15:57:08 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

#define GET_BLUE(x)		(x & 0xFF)
#define GET_GREEN(x)	((x >> 8) & 0xFF)
#define GET_RED(x)		((x >> 16) & 0xFF)
#define TO_BLUE(x)		(((int)(x)) & 0xFF)
#define TO_GREEN(x)		((((int)(x)) & 0xFF) << 8)
#define TO_RED(x)		((((int)(x)) & 0xFF) << 16)

static int	process_high_color(float relative)
{
	int		r;
	int		g;
	int		b;

	relative = (relative - MIDDLE_COLOR_PERCENT)
		/ (1 - MIDDLE_COLOR_PERCENT);
	r = relative * (GET_RED(HIGH_COLOR) - GET_RED(MIDDLE_COLOR)) \
		+ GET_RED(MIDDLE_COLOR);
	g = relative * (GET_GREEN(HIGH_COLOR) - GET_GREEN(MIDDLE_COLOR)) \
		+ GET_GREEN(MIDDLE_COLOR);
	b = relative * (GET_BLUE(HIGH_COLOR) - GET_BLUE(MIDDLE_COLOR)) \
		+ GET_BLUE(MIDDLE_COLOR);
	return (TO_RED(r) | TO_GREEN(g) | TO_BLUE(b));
}

static int	process_low_color(float relative)
{
	int		r;
	int		g;
	int		b;

	relative = relative / (MIDDLE_COLOR_PERCENT);
	r = relative * (GET_RED(MIDDLE_COLOR) - GET_RED(LOW_COLOR)) \
		+ GET_RED(LOW_COLOR);
	g = relative * (GET_GREEN(MIDDLE_COLOR) - GET_GREEN(LOW_COLOR)) \
		+ GET_GREEN(LOW_COLOR);
	b = relative * (GET_BLUE(MIDDLE_COLOR) - GET_BLUE(LOW_COLOR)) \
		+ GET_BLUE(LOW_COLOR);
	return (TO_RED(r) | TO_GREEN(g) | TO_BLUE(b));
}

int			process_color(float height)
{
	float	relative;

	if (g_max_height == g_min_height)
		return (0xFFFFFF);
	relative = (height - g_min_height) / (g_max_height - g_min_height);
	if (relative > MIDDLE_COLOR_PERCENT)
		return (process_high_color(relative));
	else
		return (process_low_color(relative));
}
