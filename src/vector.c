#include "matrix.h"
#include "libft.h"
#include <math.h>

void		fill_vector(t_vector *v, float x, float y, float z)
{
	(*v)[0] = x;
	(*v)[1] = y;
	(*v)[2] = z;
}

void		normalize_vector(t_vector *v)
{
	float	length;

	length = sqrt((*v)[0] * (*v)[0] + (*v)[1] * (*v)[1] + (*v)[2] * (*v)[2]);
	(*v)[0] /= length;
	(*v)[1] /= length;
	(*v)[2] /= length;
}

void		cross_product(t_vector *dest, t_vector u, t_vector v)
{
	(*dest)[0] = u[1] * v[2] - u[2] * v[1];
	(*dest)[1] = u[2] * v[0] - u[0] * v[2];
	(*dest)[2] = u[0] * v[1] - u[1] * v[0];
}

void		get_reversed_vector(t_vector *dest, t_vector v)
{
	(*dest)[0] = -v[0];
	(*dest)[1] = -v[1];
	(*dest)[2] = -v[2];
}
