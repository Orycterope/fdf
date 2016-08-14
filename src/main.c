#include "fdf.h"
#include "matrix.h" // not here ?
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h> //for perror

void	print_tab(int **matrix, int x, int y) // DEBUG
{
	    int		i, j;
		for (i = 0; i < y; ++i)
		{
			for (j = 0; j < x; ++j)
				ft_printf("%d ", matrix[i][j]);
			ft_printf("\n");
		}
}

static void	test_multiplication()
{
	t_matrix a;
	t_matrix b;
	t_matrix c;
	int	tabA1[] = {1, 2};
	int	tabA2[] = {3, 4};
	int	tabA3[] = {5, 6};
	int	tabA4[] = {7, 8};
	int	*tabA[] = {tabA1, tabA2, tabA3, tabA4};
	int	tabB1[] = {1, 2, 3};
	int	tabB2[] = {4, 5, 6};
	int	*tabB[] = {tabB1, tabB2};


	a.m = tabA;
	a.x_size = 2;
	a.y_size = 4;
	b.m = tabB;
	b.x_size = 3;
	b.y_size = 2;
	print_tab(a.m, a.x_size, a.y_size);
	print_tab(b.m, b.x_size, b.y_size);
	c = multiply_matrixes(a, b);
	print_tab(c.m, c.x_size, c.y_size);
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
	print_tab(grid->tab, grid->width, grid->height);
	return (0);
}
