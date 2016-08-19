#include <mlx.h>
#include "display.h"
#include "fdf.h"
#include "libft.h"
#include <stdio.h> // remove me !

t_display	display;

int	destroy_win(void *d) //really used ?
{
	(void)d;
	ft_putstr("In destroy function");
	mlx_destroy_window(display.mlx_ptr, display.win);
	exit(0);
	return (1);
}

void		init_mlx()
{
	display.mlx_ptr = mlx_init();
	display.win = mlx_new_window(display.mlx_ptr,
		WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (display.win == NULL)
	{
		ft_putstr_fd("Error while (creating mlx window", 2);
		exit(1);
	}
	mlx_hook(display.win, 17, (1L<<17), destroy_win, &display);
}

void		display_grid(t_grid *grid)
{
	int	x;
	int	y;

	mlx_clear_window(display.mlx_ptr, display.win);
	y = 0;
	while (y < grid->height)
	{
		x = 0;
		while (x < grid->width)
		{
			/*mlx_pixel_put(display.mlx_ptr, display.win,
				(int)grid->tab[y][x][0], (int)grid->tab[y][x][1],
				0xFFFFFF);*/
			mlx_string_put(display.mlx_ptr, display.win,
				(int)grid->tab[y][x][0] * 40 + WIN_WIDTH / 2,
				(int)grid->tab[y][x][1] * 40 + WIN_HEIGHT / 2,
				0xFFFFFF, ft_itoa((int)grid->tab[y][x][2]));
//			printf("Puting vertex at x: %f, y: %f, z: %f\n", grid->tab[y][x][0], grid->tab[y][x][1], grid->tab[y][x][2]); //
			x++;
		}
		y++;
	}
	free_grid(grid);
}
