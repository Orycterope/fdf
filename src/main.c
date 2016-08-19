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

static void	test_transform(t_grid *grid) //
{
	t_matrix_four	m;

	ft_bzero(&m, sizeof(t_matrix_four));
	m[0][3] = -grid->width / 2;
	m[1][3] = -grid->height / 2;
	m[0][0] = 1;
	m[1][1] = 1;
	m[2][2] = 1;
	m[3][3] = 1;
	apply_matrix_to_grid(m, grid);
}
	
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

static void	test_multiplication()
{
	t_matrix_four	a = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
	t_matrix_four	b = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
	t_matrix_four	*c;
	t_vector		v;
	t_vector		*vt;

	ft_printf("---A---\n");
	print_tab((float*)a, 4, 4);
	ft_printf("---B---\n");
	print_tab((float*)b, 4, 4);
	ft_printf("---AxB---\n");
	c = multiply_matrixes(a, b);
	print_tab((float*)c, 4, 4);
	ft_printf("---V---\n");
	fill_vector(&v, 2, 5, -3);
	print_tab((float*)v, 1, 4);
	ft_printf("---Vn---\n");
	normalize_vector(&v);
	print_tab((float*)v, 1, 4);
	ft_printf("---CxVn---\n");
	vt = multiply_matrix_vector(*c, v);
	print_tab((float*)vt, 1, 4);
	ft_printf("OK\n");
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
		test_multiplication(); //
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
	init_camera();
	test_transform(grid);
	//display_grid(grid);
	//rotate_camera('y', 1);
	project_grid(grid);
	mlx_key_hook(display.win, key_callback, grid);
	mlx_loop(display.mlx_ptr);
	return (0);
}
