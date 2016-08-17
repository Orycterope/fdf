#include "fdf.h"
#include "matrix.h"
#include "libft.h"

t_matrix_four	*multiply_matrixes(t_matrix_four a, t_matrix_four b)
{
	int				x;
	int				y;
	t_matrix_four	*new;
	int				i;

	new = (t_matrix_four*)ft_memalloc(sizeof(t_matrix_four));
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x <  4)
		{
			(*new)[y][x] = 0;
			i = 0;
			while (i < 4)
			{
				(*new)[y][x] += a[y][i] * b[i][x];
				i++;
			}
			x++;
		}
		y++;
	}
	return (new);
}

t_vector		*multiply_matrix_vector(t_matrix_four m, t_vector v)
{
	int			y;
	t_vector	*new;
	int			i;

	new = (t_vector*)ft_memalloc(sizeof(t_vector));
	y = 0;
	while (y < 4)
	{
		(*new)[y] = 0;
		i = 0;
		while (i < 4)
		{
			(*new)[y] += m[y][i] * v[i];
			i++;
		}
		y++;
	}
	return (new);
}

void			apply_matrix_to_grid(t_matrix_four m, t_grid *grid)
{
	int			x;
	int			y;
	t_vector	*new;

	y = 0;
	while (y < grid->height)
	{
		x = 0;
		while (x < grid->width)
		{
			new = multiply_matrix_vector(m, grid->tab[y][x]);
			ft_memcpy(&(grid->tab[y][x]), new, sizeof(t_vector));
			free(new);
			x++;
		}
		y++;
	}
}
