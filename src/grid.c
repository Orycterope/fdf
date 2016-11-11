#include "fdf.h"
#include "libft.h"
#include "camera.h"

t_grid	*cpy_grid(t_grid *g)
{
	t_grid	*n;
	int		y;

	n = (t_grid*)ft_memalloc(sizeof(t_grid));
	ft_memcpy(n, g, sizeof(t_grid));
	n->tab = (t_vertex**)ft_memalloc(sizeof(t_vertex*) * g->height);
	y = 0;
	while (y < g->height)
	{
		n->tab[y] = (t_vertex*)ft_memalloc(sizeof(t_vertex) * g->width);
		//ft_memcpy(&(n->tab[y]), &(g->tab[y]), sizeof(t_vector) * g->width);
		ft_memcpy(n->tab[y], g->tab[y], sizeof(t_vertex) * g->width);
		y++;
	}
	return (n);
}

void	get_new_m2w_matrix(char axe, char sens, char rot_trans)
{
	t_matrix_four	transf_m;
	float			angle;
	t_matrix_four	*new;

	if (rot_trans == 1)
	{
		angle = (sens > 0) ? ROTATION_ANGLE : -ROTATION_ANGLE;
		get_rotation_matrix(&transf_m, axe, angle);
	}
	else
	{
		fill_identity_matrix(&transf_m);
		transf_m[(int)axe][3] = (float)sens;
	}
	new = multiply_matrixes(transf_m, m2w_matrix);
	ft_memcpy(&(m2w_matrix), new, sizeof(t_matrix_four));
	free(new);
}

void	free_grid(t_grid *g)
{
	int	y;

	y = 0;
	while (y < g->height)
		free(g->tab[y++]);
	free(g);
}
