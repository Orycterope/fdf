/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 15:20:48 by tvermeil          #+#    #+#             */
/*   Updated: 2017/09/12 16:53:19 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "display.h"
#include "libft.h"
#include "fdf.h"
#include <math.h>
#include <mlx.h>

t_camera		g_camera;

void			init_camera(t_grid *grid)
{
	float	z_pos;

	z_pos = MAX(grid->width, grid->height) / tan(RAD(FOV_HALF_ANGLE)) * 1.2;
	fill_vector(&g_camera.pos, 0, 0, z_pos);
	fill_vector(&g_camera.dir, 0, 0, -1);
	fill_vector(&g_camera.up, 0, 1, 0);
}

void			rotate_camera(char axe, char sens)
{
	t_matrix_four	rot_m;
	float			angle;
	t_vector		*new_pos;
	t_vector		*new_up;

	angle = (sens > 0) ? ROTATION_ANGLE : -ROTATION_ANGLE;
	get_rotation_matrix(&rot_m, axe, angle);
	new_pos = multiply_matrix_vector(rot_m, g_camera.pos);
	new_up = multiply_matrix_vector(rot_m, g_camera.up);
	ft_memcpy(&(g_camera.pos), new_pos, sizeof(t_vector));
	ft_memcpy(&(g_camera.up), new_up, sizeof(t_vector));
	free(new_pos);
	free(new_up);
	ft_memcpy(&(g_camera.dir), &(g_camera.pos), sizeof(t_vector));
	normalize_vector(&(g_camera.dir));
	g_camera.dir[0] = -g_camera.dir[0];
	g_camera.dir[1] = -g_camera.dir[1];
	g_camera.dir[2] = -g_camera.dir[2];
}

void			translate_camera(int axe, int sens)
{
	t_vector	v;

	ft_bzero(&v, sizeof(t_vector));
	v[axe] = sens;
	g_camera.pos[0] += v[0];
	g_camera.pos[1] += v[1];
	g_camera.pos[2] += v[2];
}

void			project_grid(t_grid *g, t_matrix_four *m2w)
{
	t_list			*visible_vertices;
	void			*img;
	t_matrix_four	*combined_matrix;

	g = cpy_grid(g);
	reset_z_buffer();
	combined_matrix = get_combination_matrix(m2w);
	visible_vertices = apply_matrix_to_grid(*combined_matrix, g);
	free(combined_matrix);
	img = mlx_new_image(g_display.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	g_display.img_tab = mlx_get_data_addr(img,
		&g_display.bits_per_pixel, &g_display.img_size_line,
		&g_display.img_endian);
	display_grid(g, visible_vertices);
	mlx_put_image_to_window(g_display.mlx_ptr, g_display.win, img, 0, 0);
	mlx_destroy_image(g_display.mlx_ptr, img);
	free_grid(g);
}
