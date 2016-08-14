#include "matrix.h"
#include "libft.h"

static int	multiply_rows(t_matrix a, t_matrix b, int row, int col)
{
	int	i;
	int	value;

	value = 0;
	i = 0;
	while (i < a.x_size)
	{
		value += a.m[row][i] * b.m[i][col];
		i++;
	}
	return (value);
}

t_matrix	multiply_matrixes(t_matrix a, t_matrix b)
{
	int			x;
	int			y;
	t_matrix	new;

	new.m = NULL;
	if (a.x_size != b.y_size)
		return (new);
	new.y_size = a.y_size;
	new.x_size = b.x_size;
	new.m = ft_memalloc(sizeof(int*) * new.y_size);
	y = 0;
	while (y < new.y_size)
	{
		new.m[y] = ft_memalloc(sizeof(int) * new.x_size);
		x = 0;
		while (x < new.x_size)
		{
			new.m[y][x] = multiply_rows(a, b, y, x);
			x++;
		}
		y++;
	}
	return (new);
}
