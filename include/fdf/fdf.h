#ifndef FDF_H
# define FDF_H
# include "matrix.h"

typedef struct		s_grid
{
	int				height;
	int				width;
	t_vector		**tab;
}					t_grid;

t_grid				*parse_file(int fd);
void				apply_matrix_to_grid(t_matrix_four m, t_grid *grid);

#endif
