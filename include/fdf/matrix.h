#ifndef MATRIX_H
# define MATRIX_H

typedef	struct		s_matrix
{
		int			x_size;
		int			y_size;
		int			**m;
}					t_matrix;

t_matrix	multiply_matrixes(t_matrix m, t_matrix n);
void		free_matrix_content(t_matrix m);
t_matrix	create_vector(int x, int y, int z);
void		normalize_vector(t_matrix vector);

#endif
