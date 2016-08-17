#include "matrix.h"
#include "libft.h"
#include <math.h>

t_vector	*create_vector(int x, int y, int z)
{
	t_vector	*new;

	new = (t_vector*)ft_memalloc(sizeof(t_vector));
	(*new)[0] = x;
	(*new)[1] = y;
	(*new)[2] = z;
	(*new)[3] = 1;
	return (new);
}

void		normalize_vector(t_vector *v)
{
	float	length;

	length = sqrt((*v)[0] * (*v)[0] + (*v)[1] * (*v)[1] + (*v)[2] * (*v)[2]);
	(*v)[0] /= length;
	(*v)[1] /= length;
	(*v)[2] /= length;
}
