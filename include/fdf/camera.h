/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 17:49:47 by tvermeil          #+#    #+#             */
/*   Updated: 2017/09/11 17:56:57 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "matrix.h"
# include "fdf.h"
# define ROTATION_ANGLE 0.174533

typedef struct	s_camera
{
	t_vector	pos;
	t_vector	dir;
	t_vector	up;
}				t_camera;

void			init_camera(t_grid *grid);
void			rotate_camera(char axe, char sens);
void			project_grid(t_grid *g, t_matrix_four *m2w);

#endif
