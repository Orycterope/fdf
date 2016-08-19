#include "display.h"
#include <mlx.h>
#define ROUND(x) ((int)(x + 0.5))
#define ABS(x) (x < 0 ? -x : x)

static void draw_horizontal_line(int x1, int y1, int x2, int y2)
{
	float	dx;
	float	dy;
	int		x;

	x1 = x1 * 40 + WIN_WIDTH / 2;
	y1 = y1 * 40 + WIN_WIDTH / 2;
	x2 = x2 * 40 + WIN_WIDTH / 2;
	y2 = y2 * 40 + WIN_WIDTH / 2;
	dx = x2 - x1;
	dy = y2 - y1;
	x = x1;
	while (x <= x2)
	{
		mlx_pixel_put(display.mlx_ptr, display.win,
			x,
			y1 + dy * (x - x1) / dx,
			0xFFFFFF);
		x++;
	}
}

static void draw_vertical_line(int x1, int y1, int x2, int y2)
{
	float	dx;
	float	dy;
	int		y;

	x1 = x1 * 40 + WIN_WIDTH / 2;
	y1 = y1 * 40 + WIN_WIDTH / 2;
	x2 = x2 * 40 + WIN_WIDTH / 2;
	y2 = y2 * 40 + WIN_WIDTH / 2;
	dx = x2 - x1;
	dy = y2 - y1;
	y = y1;
	while (y <= y2)
	{
		mlx_pixel_put(display.mlx_ptr, display.win,
			x1 + dx * (y - y1) / dy,
			y,
			0xFFFFFF);
		y++;
	}
}

static void try_draw_line(int x1, int y1, int x2, int y2)
{
	if ((x1 < -WIN_WIDTH / 2 && x2 < -WIN_WIDTH / 2)
		|| (x1 > WIN_WIDTH / 2 && x2 > WIN_WIDTH / 2)
		|| (y1 < -WIN_HEIGHT / 2 && y2 < -WIN_HEIGHT / 2)
		|| (y1 > WIN_HEIGHT / 2 && y2 > WIN_HEIGHT / 2))
		return ;
		
	if ((y2 - y1) < (x2 - x1))
	{
		if (x2 > x1)
			draw_horizontal_line(x1, y1, x2, y2);
		else
			draw_horizontal_line(x2, y2, x1, y1);
	}
	else
	{
		if (y2 > y1)
			draw_vertical_line(x1, y1, x2, y2);
		else
			draw_vertical_line(x2, y2, x1, y1);
	}
}

void		draw_lines(t_grid *g)
{
	int	j;
	int	i;

	j = 0;
	while (j < g->height)
	{
		i = 0;
		while (i < g->width)
		{
			if (j > 0)
				try_draw_line(g->tab[j - 1][i][0], g->tab[j - 1][i][1], 
					g->tab[j][i][0], g->tab[j][i][1]); 
			if (i > 0)
				try_draw_line(g->tab[j][i - 1][0], g->tab[j][i - 1][1], 
					g->tab[j][i][0], g->tab[j][i][1]); 
			i++;
		}
		j++;
	}
}
