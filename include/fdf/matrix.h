#ifndef MATRIX_H
# define MATRIX_H

/*typedef	struct		s_matrix
{
		int			x_size;
		int			y_size;
		int			**m;
}					t_matrix;
*/

typedef float	t_vector[4];
typedef float	t_matrix_four[4][4];

t_matrix_four	*multiply_matrixes(t_matrix_four a, t_matrix_four b);
t_vector		*multiply_matrix_vector(t_matrix_four m, t_vector v);
t_vector		*create_vector(int x, int y, int z);
void			normalize_vector(t_vector *v);

#endif
