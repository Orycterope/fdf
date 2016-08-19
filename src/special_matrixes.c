#include "fdf.h"
#define NEAR -10
#define FAR -100

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
	(*m)[0][0] = 30; //
	(*m)[1][1] = 30; //
	(*m)[0][3] = WIN_WIDTH / 2;
	(*m)[1][3] = WIN_HEIGHT / 2;
	return (m);
}

t_matrix_four	*get_perspective_matrix()
{
	t_matrix_four	*m;

	m = (t_matrix_four*)ft_memalloc(sizeof(t_matrix_four));
	ft_bzero(m, sizeof(t_matrix_four));
	(*m)[0][0] = 1;
	(*m)[1][1] = 1;
	(*m)[2][2] = (NEAR + FAR) / NEAR;
	(*m)[2][3] = -FAR;
	(*m)[3][2] = 1 / NEAR;
	return (m);
}
