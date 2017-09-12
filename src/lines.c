/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 17:50:44 by tvermeil          #+#    #+#             */
/*   Updated: 2017/09/12 15:57:42 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include <mlx.h>
#include <float.h>
#define ROUND(x)	((int)(x + 0.5))
#define ABS(x)		(x < 0 ? -(x) : (x))
#define X(v)		(v.pos[0])
#define Y(v)		(v.pos[1])
#define Z(v)		(v.pos[2])
#define H(v)		(v.height)

extern float	g_max_height;
extern float	g_min_height;

static void		draw_pixel(t_vertex v, float intensity)
{
	unsigned int	color;
	unsigned char	component;
	int				i;
	size_t			pos;

	if ((int)X(v) <= 0 || X(v) >= WIN_WIDTH || (int)Y(v) <= 0
		|| Y(v) >= WIN_HEIGHT || intensity <= 0
		|| Z(v) > g_display.z_buffer[(int)Y(v)][(int)X(v)] || (intensity < 1
			&& g_display.z_buffer[(int)Y(v)][(int)X(v)] != FLT_MAX))
		return ;
	color = process_color(v.height);
	color = mlx_get_color_value(g_display.mlx_ptr, color);
	pos = ((int)Y(v)) * g_display.img_size_line
		+ ((int)X(v)) * g_display.bits_per_pixel / 8;
	i = -1;
	while (++i * 8 < g_display.bits_per_pixel)
	{
		component = (unsigned char)color * intensity;
		if (intensity < 1)
			component += g_display.img_tab[pos + i] * (1 - intensity);
		g_display.img_tab[pos + i] = component;
		color >>= 8;
	}
	if (intensity == 1)
		g_display.z_buffer[(int)Y(v)][(int)X(v)] = Z(v);
}

static void		draw_horizontal_line(t_vertex v1, t_vertex v2)
{
	float		dx;
	float		dy;
	t_vertex	p;
	t_vertex	n;

	dx = X(v2) - X(v1);
	dy = Y(v2) - Y(v1);
	X(p) = X(v1);
	while (X(p) <= X(v2))
	{
		Y(p) = Y(v1) + dy * (X(p) - X(v1)) / dx;
		Z(p) = Z(v1) + (Z(v2) - Z(v1)) * (X(p) - X(v1)) / dx;
		H(p) = H(v1) + (H(v2) - H(v1)) * (X(p) - X(v1)) / dx;
		n = p;
		Y(n) = Y(p) + 1;
		draw_pixel(n, Y(p) - (int)(Y(p)));
		Y(n) = Y(p);
		draw_pixel(n, 1.0);
		Y(n) = Y(p) - 1;
		draw_pixel(n, (int)(Y(p) + 1) - Y(p));
		X(p)++;
	}
}

static void		draw_vertical_line(t_vertex v1, t_vertex v2)
{
	float		dx;
	float		dy;
	t_vertex	p;
	t_vertex	n;

	dx = X(v2) - X(v1);
	dy = Y(v2) - Y(v1);
	Y(p) = Y(v1);
	while (Y(p) <= Y(v2))
	{
		X(p) = X(v1) + dx * (Y(p) - Y(v1)) / dy;
		Z(p) = Z(v1) + (Z(v2) - Z(v1)) * (Y(p) - Y(v1)) / dy;
		H(p) = H(v1) + (H(v2) - H(v1)) * (Y(p) - Y(v1)) / dy;
		n = p;
		X(n) = X(p) + 1;
		draw_pixel(n, X(p) - (int)(X(p)));
		X(n) = X(p);
		draw_pixel(n, 1.0);
		X(n) = X(p) - 1;
		draw_pixel(n, (int)(X(p) + 1) - X(p));
		Y(p)++;
	}
}

void			try_draw_line(t_vertex v1, t_vertex v2)
{
	if ((X(v1) < 0 && X(v2) < 0)
		|| (X(v1) > WIN_WIDTH && X(v2) > WIN_WIDTH)
		|| (Y(v1) < 0 && Y(v2) < 0)
		|| (Y(v1) > WIN_HEIGHT && Y(v2) > WIN_HEIGHT))
		return ;
	if (ABS(Y(v2) - Y(v1)) < ABS(X(v2) - X(v1)))
	{
		if (X(v2) > X(v1))
			draw_horizontal_line(v1, v2);
		else
			draw_horizontal_line(v2, v1);
	}
	else
	{
		if (Y(v2) > Y(v1))
			draw_vertical_line(v1, v2);
		else
			draw_vertical_line(v2, v1);
	}
}
