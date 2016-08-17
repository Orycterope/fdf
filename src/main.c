#include "fdf.h"
#include "matrix.h" // not here ?
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h> //for perror

void	print_tab(float *matrix, int x, int y) // DEBUG
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
	t_vector		*v;
	t_vector		*vt;

	ft_printf("---A---\n");
	print_tab((float*)a, 4, 4);
	ft_printf("---B---\n");
	print_tab((float*)b, 4, 4);
	ft_printf("---AxB---\n");
	c = multiply_matrixes(a, b);
	print_tab((float*)c, 4, 4);
	ft_printf("---V---\n");
	v = create_vector(2, 5, -3);
	print_tab((float*)v, 1, 4);
	ft_printf("---Vn---\n");
	normalize_vector(v);
	print_tab((float*)v, 1, 4);
	ft_printf("---CxVn---\n");
	vt = multiply_matrix_vector(*c, *v);
	print_tab((float*)vt, 1, 4);
	ft_printf("OK\n");
}

int	main(int ac, char **av)
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
	(void)grid;
//	print_tab(grid->tab, grid->width, grid->height);
	return (0);
}
