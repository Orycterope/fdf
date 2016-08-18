#include "fdf.h"
#include "libft.h"

t_grid	*cpy_grid(t_grid *g)
{
	t_grid	*n;
	int		y;
	
	n = ft_memalloc(sizeof(t_grid));
	ft_memcpy(n, g, sizeof(t_grid));
	n->tab = ft_memalloc(sizeof(t_vector*) * g->height);
	y = 0;
	while (y < g->height)
	{
		n->tab[y] = ft_memalloc(sizeof(t_vector) * g->width);
		ft_memcpy(&(n->tab[y]), &(g->tab[y]), sizeof(t_vector) * g->width);
		y++;
	}
	return (n);
}

void	free_grid(t_grid *g)
{
	int	y;
	
	y = 0;
	while (y < g->height)
		free(g->tab[y++]);
	free(g);
}
