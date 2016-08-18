#ifndef CAMERA_H
# define CAMERA_H
# include "matrix.h"
# include "fdf.h"
# define ROTATION_ANGLE 0.174533

typedef struct	s_camera
{
	t_vector	pos;
	t_vector	dir;
}				t_camera;

extern t_camera	camera;

void			init_camera();
void			rotate_camera(char axe, char sens);
void			project_grid(t_grid *g);

#endif
