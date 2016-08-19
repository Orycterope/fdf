#ifndef FDF_H
# define FDF_H
# include "matrix.h"
# include "libft.h"

typedef struct		s_grid
{
	int				height;
	int				width;
	t_vector		**tab;
}					t_grid;

t_grid				*parse_file(int fd);
void				apply_matrix_to_grid(t_matrix_four m, t_grid *grid);
t_grid				*cpy_grid(t_grid *g);
void				free_grid(t_grid *g);

# include "display.h"
#endif
