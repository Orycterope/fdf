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
		rotate_camera('x', -1);
	else if (keycode == KEY_S)
		rotate_camera('x', 1);
	else if (keycode == KEY_A)
		rotate_camera('y', 1);
	else if (keycode == KEY_D)
		rotate_camera('y', -1);
	else if (keycode == KEY_Z)
		translate_camera(2, 1);
	else if (keycode == KEY_X)
		translate_camera(2, -1);
	else
	{
		printf("pressed keycode %d\n", keycode);	 //
		return (0);
	}
	project_grid(param);
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
	project_grid(grid);
	mlx_key_hook(display.win, key_callback, grid);
	mlx_loop(display.mlx_ptr);
	return (0);
}
