#include "matrix.h"
#include "libft.h"
#include <math.h>

t_matrix	create_vector(int x, int y, int z)
{
	t_matrix	new;
	int			i;

	new.x_size = 1;
	new.y_size = 4;
	new.m = ft_memalloc(sizeof(int*) * 4);
	i = 0;
	while (i < 4)
		new.m[i++] = ft_memalloc(sizeof(int));
	new.m[0][0] = x;
	new.m[1][0] = y;
	new.m[2][0] = z;
	new.m[3][0] = 1;
	return (new);
}

void		normalize_vector(t_matrix vector)
{
	float	length;
	int		**t;

	t = vector.m;
	length = sqrt(t[0][0] * t[0][0] + t[1][0] * t[1][0] + t[2][0] * t[2][0]); 
	t[0][0] /= length;
	t[1][0] /= length;
	t[2][0] /= length;
}
