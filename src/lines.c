#include "display.h"
#include <mlx.h>
#include <math.h>
#define ROUND(x)	((int)(x + 0.5))
#define ABS(x)		(x < 0 ? -(x) : (x))
#define GET_BLUE(x)		(x & 0xFF)
#define GET_GREEN(x)	((x >> 8) & 0xFF)
#define GET_RED(x)		((x >> 16) & 0xFF)
#define TO_BLUE(x)		(((int)(x)) & 0xFF)
#define TO_GREEN(x)		((((int)(x)) & 0xFF) << 8)
#define TO_RED(x)		((((int)(x)) & 0xFF) << 16)
#define X(v)		(v.pos[0])
#define Y(v)		(v.pos[1])
#define Z(v)		(v.pos[2])
#define H(v)		(v.height)

extern float	max_height;
extern float	min_height;

static int		process_color(float height)
{
	float	relative;
	int		r;
	int		g;
	int		b;

	relative = (height - min_height) / max_height;

	r = relative * (GET_RED(HIGH_COLOR) - GET_RED(LOW_COLOR)) \
		+ GET_RED(LOW_COLOR);
	g = relative * (GET_GREEN(HIGH_COLOR) - GET_GREEN(LOW_COLOR)) \
		+ GET_GREEN(LOW_COLOR);
	b = relative * (GET_BLUE(HIGH_COLOR) - GET_BLUE(LOW_COLOR)) \
		+ GET_BLUE(LOW_COLOR);
	return (TO_RED(r) | TO_GREEN(g) | TO_BLUE(b));
}

static void draw_pixel(t_vertex v, float intensity)
{
	unsigned int	color;
	int				i;
	size_t			pos;

	if ((int)X(v) <= 0 || X(v) >= WIN_WIDTH || (int)Y(v) <= 0 || Y(v) >= WIN_HEIGHT
		|| intensity < 0 || Z(v) < display.z_buffer[(int)Y(v)][(int)X(v)])
		return;
	color = process_color(v.height);
	color = mlx_get_color_value(display.mlx_ptr, color);
	pos = ((int)Y(v)) * display.img_size_line + ((int)X(v)) * display.bits_per_pixel / 8;
	i = 0;
	while (i * 8 < display.bits_per_pixel)
	{
		if ((unsigned char)color * intensity > (unsigned char)display.img_tab[pos + i])
			display.img_tab[pos + i] = (unsigned char)color * intensity;
		color >>= 8;
		i++;
	}
}

static void draw_horizontal_line(t_vertex v1, t_vertex v2)
{
	float	dx;
	float	dy;
	t_vertex	p;
	t_vertex	n;

	dx =  X(v2) - X(v1);
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

static void draw_vertical_line(t_vertex v1, t_vertex v2)
{
	float	dx;
	float	dy;
	t_vertex	p;
	t_vertex	n;

	dx =  X(v2) - X(v1);
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

void		try_draw_line(t_vertex v1, t_vertex v2)
{
	if ((X(v1) < 0 && X(v2) < 0)
		|| (X(v1) > WIN_WIDTH && X(v2) > WIN_WIDTH)
		|| (Y(v1) < 0 && Y(v2) < 0)
		|| (Y(v1) > WIN_HEIGHT && Y(v2) > WIN_HEIGHT))
		return;

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
