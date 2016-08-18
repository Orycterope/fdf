#include "camera.h"
#include "display.h"
#include "libft.h"
#include <math.h>

t_camera		camera;

void			init_camera()
{
	fill_vector(&camera.pos, 0, 0, 10);
	fill_vector(&camera.dir, 0, 0, -1);
}

static void		get_rotation_matrix(t_matrix_four *m, char axe, float angle)
{
	ft_bzero(m, sizeof(t_matrix_four));
	(*m)[3][3] = 1;
	if (axe == 'x')
	{
		(*m)[0][0] = 1;
		(*m)[1][1] = (float)cos(angle);
		(*m)[1][2] = (float)-sin(angle);
		(*m)[2][1] = (float)sin(angle);
		(*m)[2][2] = (float)cos(angle);
	}
	else if (axe == 'y')
	{
		(*m)[0][0] = (float)cos(angle);
		(*m)[0][2] = (float)sin(angle);
		(*m)[1][1] = 1;
		(*m)[2][0] = (float)-sin(angle);
		(*m)[2][2] = (float)cos(angle);
	}
}

void			rotate_camera(char axe, char sens)
{
	t_matrix_four	rot_m;
	float			angle;
	t_vector		*new_pos;

	angle = (sens > 0) ? ROTATION_ANGLE : -ROTATION_ANGLE;
	get_rotation_matrix(&rot_m, axe, angle);
	new_pos = multiply_matrix_vector(rot_m, camera.pos);
	ft_memcpy(&(camera.pos), new_pos, sizeof(t_vector));
	free(new_pos);
	ft_memcpy(&(camera.dir), &(camera.pos), sizeof(t_vector));
	normalize_vector(&(camera.dir));
	camera.dir[0] = -camera.dir[0];
	camera.dir[1] = -camera.dir[1];
	camera.dir[2] = -camera.dir[2];
}	

t_matrix_four	*get_projection_matrix() //static
{
	t_matrix_four	m;
	t_vector		s;
	t_vector		u;
	t_vector		up;
	t_matrix_four	t;

	ft_bzero(&m, sizeof(t_matrix_four));
	ft_bzero(&up, sizeof(t_vector));
	up[1] = 1;
	cross_product(&s, camera.dir, up);
	cross_product(&u, s, camera.dir);
	normalize_vector(&s);
	normalize_vector(&u);
	ft_memcpy(&(m[0]), &s, sizeof(t_vector));
	ft_memcpy(&(m[1]), &u, sizeof(t_vector));
	get_reversed_vector(&(m[2]), camera.dir);
	m[3][3] = 1;
	fill_identity_matrix(&t);
	t[0][3] = -camera.pos[0];
	t[1][3] = -camera.pos[1];
	t[2][3] = -camera.pos[2];
	return (multiply_matrixes(m, t));
}

void			project_grid(t_grid *g)
{
	t_matrix_four	*proj_m;

	g = cpy_grid(g);
	proj_m = get_projection_matrix();
	apply_matrix_to_grid(*proj_m, g);
	free(proj_m);
	display_grid(g); //render ?
}
