#ifndef MATRIX_H
# define MATRIX_H

typedef	struct		s_matrix
{
		int			x_size;
		int			y_size;
		int			**m;
}					t_matrix;

//typedef int[1][3]	t_vector;

t_matrix	multiply_matrixes(t_matrix m, t_matrix n);
#endif
