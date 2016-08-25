#include "fdf.h"
#include <math.h>
#define NEAR 1
#define FAR 40
#define FOV_HALF_ANGLE 50
#define RAD(a) (a * M_PI / 180)

t_matrix_four	*get_camera_offset_matrix()
{
	t_matrix_four	*m;
	int				i;

	m = (t_matrix_four*)ft_memalloc(sizeof(t_matrix_four));
	ft_bzero(m, sizeof(t_matrix_four));
	i = -1;
	while (++i < 4)
		(*m)[i][i] = 1;
	// upscale
	(*m)[0][0] = WIN_WIDTH; //
	(*m)[1][1] = WIN_WIDTH; //
	(*m)[0][3] = WIN_WIDTH / 2;
	(*m)[1][3] = WIN_HEIGHT / 2;
	return (m);
}

t_matrix_four	*get_perspective_matrix()
{
	t_matrix_four	*m;

	m = (t_matrix_four*)ft_memalloc(sizeof(t_matrix_four));
	ft_bzero(m, sizeof(t_matrix_four));
	(*m)[0][0] = 1 / (tan(RAD(FOV_HALF_ANGLE)));
	(*m)[1][1] = 1 / (tan(RAD(FOV_HALF_ANGLE)));
	(*m)[2][2] = -FAR / (FAR - NEAR);
	(*m)[2][3] = -(FAR * NEAR) / (FAR - NEAR);
	(*m)[3][2] = -1;
	return (m);
}
