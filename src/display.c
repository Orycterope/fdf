/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 14:15:38 by tvermeil          #+#    #+#             */
/*   Updated: 2017/09/12 15:10:21 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <float.h>
#include "display.h"
#include "fdf.h"
#include "libft.h"

t_display		g_display;
t_matrix_four	g_m2w_matrix;

void		reset_z_buffer(void)
{
	int		l;
	int		c;

	l = -1;
	while (++l < WIN_HEIGHT)
	{
		c = -1;
		while (++c < WIN_WIDTH)
			g_display.z_buffer[l][c] = FLT_MAX;
	}
}

static void	init_z_buffer(void)
{
	int		l;

	g_display.z_buffer = (float **)ft_memalloc(sizeof(float *) * WIN_HEIGHT);
	l = -1;
	while (++l < WIN_HEIGHT)
		g_display.z_buffer[l] = (float *)ft_memalloc(sizeof(float) * WIN_WIDTH);
}

/*
** static void	free_z_buffer(void)
** {
** 	int		l;
**
** 	l = -1;
** 	while (++l < WIN_HEIGHT)
** 		free(g_display.z_buffer[l]);
** 	free(g_display.z_buffer);
** 	g_display.z_buffer = NULL;
** }
**
** int			destroy_win(void *d) //really used ?
** {
** 	(void)d;
** 	ft_putstr("In destroy function");
** 	mlx_destroy_window(g_display.mlx_ptr, g_display.win);
** 	free_z_buffer();
** 	exit(0);
** 	return (1);
** }
*/

void		init_mlx(void)
{
	g_display.mlx_ptr = mlx_init();
	g_display.win = mlx_new_window(g_display.mlx_ptr,
		WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (g_display.win == NULL)
	{
		ft_putstr_fd("Error while creating mlx window", 2);
		exit(1);
	}
	init_z_buffer();
}

void		display_grid(t_grid *g, t_list *l)
{
	t_tupple	c;
	t_list		*next;

	mlx_clear_window(g_display.mlx_ptr, g_display.win);
	while (l != NULL)
	{
		c = *((t_tupple*)l->content);
		if (c.y > 0)
			try_draw_line(g->tab[c.y - 1][c.x], g->tab[c.y][c.x]);
		if (c.x > 0)
			try_draw_line(g->tab[c.y][c.x - 1], g->tab[c.y][c.x]);
		if (c.y < g->height - 1 && !is_displayable(g->tab[c.y + 1][c.x].pos))
			try_draw_line(g->tab[c.y + 1][c.x], g->tab[c.y][c.x]);
		if (c.x < g->width - 1 && !is_displayable(g->tab[c.y][c.x + 1].pos))
			try_draw_line(g->tab[c.y][c.x + 1], g->tab[c.y][c.x]);
		next = l->next;
		free(l->content);
		free(l);
		l = next;
	}
}

int			is_displayable(t_vector v)
{
	return (v[0] >= 0 && v[0] <= WIN_WIDTH
			&& v[1] >= 0 && v[1] <= WIN_HEIGHT
			&& v[2] >= 0 && v[2] <= 1);
}
