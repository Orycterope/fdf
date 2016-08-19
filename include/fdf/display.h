#ifndef DISPLAY_H
# define DISPLAY_H
# include "fdf.h"
# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define WIN_TITLE "fdf"
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100

typedef struct		s_display
{
	void			*mlx_ptr;
	void			*win;
	void			*img;
}					t_display;

extern t_display	display;

void				init_mlx();
void				display_grid(t_grid *grid);
void				draw_lines(t_grid *g);

#endif
