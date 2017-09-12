/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_matrixes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 17:52:45 by tvermeil          #+#    #+#             */
/*   Updated: 2017/09/12 17:05:14 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "display.h"
#include "camera.h"
#include <math.h>
#define NEAR 1
#define FAR 40

extern t_camera	g_camera;

t_matrix_four	*get_camera_offset_matrix(void)
{
	t_matrix_four	*m;
	int				i;

	m = (t_matrix_four*)ft_memalloc(sizeof(t_matrix_four));
	ft_bzero(m, sizeof(t_matrix_four));
	i = -1;
	while (++i < 4)
		(*m)[i][i] = 1;
	(*m)[0][0] = WIN_WIDTH;
	(*m)[1][1] = WIN_HEIGHT;
	(*m)[0][3] = WIN_WIDTH / 2;
	(*m)[1][3] = WIN_HEIGHT / 2;
	return (m);
}

t_matrix_four	*get_perspective_matrix(void)
{
	t_matrix_four	*m;
	float			top;
	float			bottom;
	float			right;
	float			left;

	m = (t_matrix_four*)ft_memalloc(sizeof(t_matrix_four));
	ft_bzero(m, sizeof(t_matrix_four));
	right = tan(RAD(FOV_HALF_ANGLE)) * NEAR;
	left = -right;
	top = right * WIN_HEIGHT / WIN_WIDTH;
	bottom = -top;
	(*m)[0][0] = 2 * NEAR / (right - left);
	(*m)[0][2] = (right + left) / (right - left);
	(*m)[1][1] = 2 * NEAR / (top - bottom);
	(*m)[1][2] = (top + bottom) / (top - bottom);
	(*m)[2][2] = -(FAR + NEAR) / (FAR - NEAR);
	(*m)[2][3] = -(2 * FAR * NEAR) / (FAR - NEAR);
	(*m)[3][2] = -1;
	return (m);
}

void			get_rotation_matrix(t_matrix_four *m, char axe, float angle)
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

t_matrix_four	*get_projection_matrix(void)
{
	t_matrix_four	m;
	t_vector		s;
	t_vector		u;
	t_matrix_four	t;

	ft_bzero(&m, sizeof(t_matrix_four));
	cross_product(&s, g_camera.dir, g_camera.up);
	cross_product(&u, s, g_camera.dir);
	normalize_vector(&s);
	normalize_vector(&u);
	ft_memcpy(&(m[0]), &s, sizeof(t_vector));
	ft_memcpy(&(m[1]), &u, sizeof(t_vector));
	get_reversed_vector((t_vector*)&(m[2]), g_camera.dir);
	m[3][3] = 1;
	fill_identity_matrix(&t);
	t[0][3] = -g_camera.pos[0];
	t[1][3] = -g_camera.pos[1];
	t[2][3] = -g_camera.pos[2];
	return (multiply_matrixes(m, t));
}

t_matrix_four	*get_combination_matrix(t_matrix_four *m2w)
{
	t_matrix_four	*m2;
	t_matrix_four	*m1;
	t_matrix_four	*res;

	m1 = get_camera_offset_matrix();
	m2 = get_perspective_matrix();
	res = multiply_matrixes(*m1, *m2);
	free(m1);
	free(m2);
	m1 = res;
	m2 = get_projection_matrix();
	res = multiply_matrixes(*m1, *m2);
	free(m1);
	free(m2);
	m1 = res;
	res = multiply_matrixes(*m1, *m2w);
	free(m1);
	return (res);
}
