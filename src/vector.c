#include "matrix.h"
#include "libft.h"
#include <math.h>

void		fill_vector(t_vector *v, float x, float y, float z)
{
	(*v)[0] = x;
	(*v)[1] = y;
	(*v)[2] = z;
	(*v)[3] = 1;
}

void		normalize_vector(t_vector *v)
{
	float	length;

	length = sqrt((*v)[0] * (*v)[0] + (*v)[1] * (*v)[1] + (*v)[2] * (*v)[2]);
	(*v)[0] /= length;
	(*v)[1] /= length;
	(*v)[2] /= length;
}
