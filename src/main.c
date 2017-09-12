/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 12:54:52 by tvermeil          #+#    #+#             */
/*   Updated: 2017/09/12 17:28:40 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "display.h"
#include "libft.h"
#include "camera.h"
#include <mlx.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

int			key_callback_2(int keycode)
{
	if (keycode == KEY_ESC || keycode == KEY_Q)
		exit(0);
	return (0);
}

int			key_callback(int keycode, void *param)
{
	if (keycode == KEY_W)
		get_new_m2w_matrix('x', -1, 1);
	else if (keycode == KEY_S)
		get_new_m2w_matrix('x', 1, 1);
	else if (keycode == KEY_A)
		get_new_m2w_matrix('y', 1, 1);
	else if (keycode == KEY_D)
		get_new_m2w_matrix('y', -1, 1);
	else if (keycode == KEY_I)
		get_new_m2w_matrix(1, 1, 0);
	else if (keycode == KEY_K)
		get_new_m2w_matrix(1, -1, 0);
	else if (keycode == KEY_J)
		get_new_m2w_matrix(0, 1, 0);
	else if (keycode == KEY_L)
		get_new_m2w_matrix(0, -1, 0);
	else if (keycode == KEY_U)
		get_new_m2w_matrix(2, 1, 0);
	else if (keycode == KEY_O)
		get_new_m2w_matrix(2, -1, 0);
	else
		return (key_callback_2(keycode));
	project_grid(param, &g_m2w_matrix);
	return (0);
}

int			print_usage(char **av)
{
	ft_printf("Usage: %s file.fdf\n", av[0]);
	exit(1);
}

int			main(int ac, char **av)
{
	t_grid	*grid;
	int		fd;

	if (ac < 2)
		print_usage(av);
	if ((fd = open(av[1], O_RDONLY)) == -1)
	{
		perror(av[1]);
		exit(1);
	}
	grid = parse_file(fd);
	if (!grid)
	{
		ft_putstr_fd("This is not a valid map\n", 2);
		exit(1);
	}
	init_mlx();
	init_camera(grid);
	fill_identity_matrix(&g_m2w_matrix);
	project_grid(grid, &g_m2w_matrix);
	mlx_key_hook(g_display.win, key_callback, grid);
	mlx_loop(g_display.mlx_ptr);
	return (0);
}
