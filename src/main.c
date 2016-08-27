#include "fdf.h"
#include "matrix.h" // not here ?
#include "display.h"
#include "libft.h"
#include "camera.h"
#include <mlx.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h> //for perror

void		print_tab(float *matrix, int x, int y) // DEBUG
{
	    int		i, j;
		for (i = 0; i < y; ++i)
		{
			for (j = 0; j < x; ++j)
				printf("%6.2f ", matrix[i * x + j]); //
			printf("\n");
		}
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
		get_new_m2w_matrix(2, 1, 0); //translate camera
	else if (keycode == KEY_O)
		get_new_m2w_matrix(2, -1, 0);
	else
	{
		printf("pressed keycode %d\n", keycode);	 //
		return (0);
	}
	project_grid(param, &m2w_matrix);
	return (0);
}

int			main(int ac, char **av)
{
	t_grid	*grid;
	int		fd;

	if (ac < 2)
	{
		ft_printf("Usage: %s file.fdf\n", av[0]);
		exit(1);
	}
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
	fill_identity_matrix(&m2w_matrix);
	project_grid(grid, &m2w_matrix);
	mlx_key_hook(display.win, key_callback, grid);
	mlx_loop(display.mlx_ptr);
	return (0);
}
