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

typedef struct		s_tupple
{
	int				x;
	int				y;
}					t_tupple;

t_grid				*parse_file(int fd);
t_list				*apply_matrix_to_grid(t_matrix_four m, t_grid *grid);
t_grid				*cpy_grid(t_grid *g);
void				free_grid(t_grid *g);
int					is_displayable(t_vector v);
void 				try_draw_line(int x1, int y1, int x2, int y2);

# include "display.h"
#endif
