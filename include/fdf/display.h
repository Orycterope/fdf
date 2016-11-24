#ifndef DISPLAY_H
# define DISPLAY_H
# include "fdf.h"
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define WIN_TITLE "fdf"
# ifdef __APPLE__
#  define KEY_W 13
#  define KEY_S 1
#  define KEY_A 0
#  define KEY_D 2
#  define KEY_I 34
#  define KEY_K 40
#  define KEY_J 38
#  define KEY_L 37
#  define KEY_U 32
#  define KEY_O 31
# else
#  define KEY_W 119
#  define KEY_S 115
#  define KEY_A 97
#  define KEY_D 100
#  define KEY_I 105
#  define KEY_K 107
#  define KEY_J 106
#  define KEY_L 108
#  define KEY_U 117
#  define KEY_O 111
# endif
typedef struct		s_display
{
	void			*mlx_ptr;
	void			*win;
	char			*img_tab;
	float			**z_buffer;
	int				bits_per_pixel;
	int				img_size_line;
	int				img_endian;
}					t_display;

extern t_display	display;
extern t_matrix_four	m2w_matrix;

void				init_mlx();
void				display_grid(t_grid *grid, t_list *lst);
void				draw_lines(t_grid *g);
void				reset_z_buffer();

#endif
