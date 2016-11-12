#ifndef FDF_H
# define FDF_H
# include "matrix.h"
# include "libft.h"
# define FOV_HALF_ANGLE 50
# define RAD(a) (a * M_PI / 180)
# define MAX(a, b) (a > b ? a : b)
# define HIGH_COLOR 0xFF0000
# define LOW_COLOR 0x0000FF

typedef struct		s_vertex
{
	t_vector		pos;
	int				color;
}					t_vertex;

typedef struct		s_grid
{
	int				height;
	int				width;
	t_vertex		**tab;
	float			max_height;
	float			min_height;
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
void				try_draw_line(t_vertex v1, t_vertex v2);
void				translate_camera(int axe, int sens);
void				get_new_m2w_matrix(char axe, char sens, char rot_trans);
void				get_rotation_matrix(t_matrix_four *m, char axe, float angle);

# include "display.h"
#endif
