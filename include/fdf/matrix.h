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
void			fill_vector(t_vector *v, float x, float y, float z);
void			normalize_vector(t_vector *v);
void			cross_product(t_vector *dest, t_vector u, t_vector v);
void			get_reversed_vector(t_vector *dest, t_vector v);
void			fill_identity_matrix(t_matrix_four *dest);
t_matrix_four	*get_camera_offset_matrix();
t_matrix_four	*get_perspective_matrix();

#endif
