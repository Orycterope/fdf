#include <mlx.h>
#include <float.h>
#include "display.h"
#include "fdf.h"
#include "libft.h"
#include <stdio.h> // remove me !

t_display		display;
t_matrix_four	m2w_matrix;

void		reset_z_buffer()
{
	int		l;
	int		c;

	l = -1;
	while (++l < WIN_HEIGHT)
	{
		c = -1;
		while (++c < WIN_WIDTH)
			display.z_buffer[l][c] = FLT_MIN;
	}
}

static void	init_z_buffer()
{
	int		l;

	display.z_buffer = (float **)ft_memalloc(sizeof(float *) * WIN_HEIGHT);
	l = -1;
	while (++l < WIN_HEIGHT)
		display.z_buffer[l] = (float *)ft_memalloc(sizeof(float) * WIN_WIDTH);
}

static void	free_z_buffer()
{
	int		l;

	l = -1;
	while (++l < WIN_HEIGHT)
		free(display.z_buffer[l]);
	free(display.z_buffer);
	display.z_buffer = NULL;
}

int			destroy_win(void *d) //really used ?
{
	(void)d;
	ft_putstr("In destroy function");
	mlx_destroy_window(display.mlx_ptr, display.win);
	free_z_buffer();
	exit(0);
	return (1);
}

void		init_mlx()
{
	display.mlx_ptr = mlx_init();
	display.win = mlx_new_window(display.mlx_ptr,
		WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (display.win == NULL)
	{
		ft_putstr_fd("Error while (creating mlx window", 2);
		exit(1);
	}
	init_z_buffer();
	//mlx_hook(display.win, 17, (1L<<17), destroy_win, &display);
}

void		display_grid(t_grid *g, t_list *l)
{
	t_tupple	c;
	t_list		*next;

	mlx_clear_window(display.mlx_ptr, display.win);
	while (l != NULL)
	{
		c = *((t_tupple*)l->content);
	/*mlx_string_put(display.mlx_ptr, display.win,
		(int)g->tab[c.y][c.x].pos[0],
		(int)g->tab[c.y][c.x].pos[1],
		g->tab[c.y][c.x].color, ft_itoa((int)g->tab[c.y][c.x].pos[2])); */
//		printf("Puting vertex at x: %f, y: %f, z: %f\n", grid->tab[y][x][0], grid->tab[y][x][1], grid->tab[y][x][2]); //
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
