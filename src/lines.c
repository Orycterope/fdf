#include "display.h"
#include <mlx.h>
#include <math.h>
#define ROUND(x) ((int)(x + 0.5))
#define ABS(x) (x < 0 ? -(x) : (x))

static void draw_pixel(int x, int y, unsigned int c, float intensity)
{
	unsigned int	color;
	int				i;
	size_t			pos;

	if (x <= 0 || x >= WIN_WIDTH || y <= 0 || y >= WIN_HEIGHT || intensity < 0)
		return;
	color = mlx_get_color_value(display.mlx_ptr, c);
	pos = y * display.img_size_line + x * display.bits_per_pixel / 8 ;
	i = 0;
	while (i * 8 < display.bits_per_pixel)
	{
		if ((unsigned char)color * intensity > (unsigned char)display.img_tab[pos + i])
			display.img_tab[pos + i] = (unsigned char)color * intensity;
		color >>= 8;
		i++;
	}
}

static void draw_horizontal_line(int x1, int y1, int x2, int y2)
{
	float	dx;
	float	dy;
	int		x;
	float	y;

	dx = x2 - x1;
	dy = y2 - y1;
	x = x1;
	while (x <= x2)
	{
		y = y1 + dy * (x - x1) / dx;
		draw_pixel(x, y + 1, 0xFFFFFF, y - (int)(y));
		draw_pixel(x, y, 0xFFFFFF, 1.0);
		draw_pixel(x, y - 1, 0xFFFFFF, (int)(y + 1) - y);
		x++;
	}
}

static void draw_vertical_line(int x1, int y1, int x2, int y2)
{
	float	dx;
	float	dy;
	int		y;
	float	x;

	dx = x2 - x1;
	dy = y2 - y1;
	y = y1;
	while (y <= y2)
	{
		x = x1 + dx * (y - y1) / dy;
		draw_pixel(x + 1, y, 0xFFFFFF, x - (int)(x));
		draw_pixel(x, y, 0xFFFFFF, 1.0);
		draw_pixel(x - 1, y, 0xFFFFFF, (int)(x + 1) - x);
		y++;
	}
}

void		try_draw_line(int x1, int y1, int x2, int y2)
{
	if ((x1 < 0 && x2 < 0)
		|| (x1 > WIN_WIDTH && x2 > WIN_WIDTH)
		|| (y1 < 0 && y2 < 0)
		|| (y1 > WIN_HEIGHT && y2 > WIN_HEIGHT))
		return;

	if (ABS(y2 - y1) < ABS(x2 - x1))
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
