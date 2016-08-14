#include "fdf.h"
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

int	main(int ac, char **av)
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
	(void)grid;
	print_tab(grid->tab, grid->width, grid->height);
	return (0);
}
