/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 15:11:47 by tvermeil          #+#    #+#             */
/*   Updated: 2017/09/12 15:18:43 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "matrix.h"
#include "libft.h"

t_matrix_four	*multiply_matrixes(t_matrix_four a, t_matrix_four b)
{
	int				x;
	int				y;
	t_matrix_four	*new;
	int				i;

	new = (t_matrix_four*)ft_memalloc(sizeof(t_matrix_four));
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			(*new)[y][x] = 0;
			i = 0;
			while (i < 4)
			{
				(*new)[y][x] += a[y][i] * b[i][x];
				i++;
			}
			x++;
		}
		y++;
	}
	return (new);
}

t_vector		*multiply_matrix_vector(t_matrix_four m, t_vector v)
{
	t_vector	*new;
	float		w;

	new = (t_vector*)ft_memalloc(sizeof(t_vector));
	(*new)[0] = m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3];
	(*new)[1] = m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3];
	(*new)[2] = m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3];
	w = m[3][0] * v[0] + m[3][1] * v[1] + m[3][2] * v[2] + m[3][3];
	if (w != 1)
	{
		(*new)[0] /= w;
		(*new)[1] /= w;
		(*new)[2] /= w;
	}
	return (new);
}

t_list			*apply_matrix_to_grid(t_matrix_four m, t_grid *grid)
{
	t_vector	*new;
	t_list		*lst;
	t_tupple	coord;

	lst = NULL;
	coord.y = 0;
	while (coord.y < grid->height)
	{
		coord.x = 0;
		while (coord.x < grid->width)
		{
			new = multiply_matrix_vector(m, grid->tab[coord.y][coord.x].pos);
			ft_memcpy(&(grid->tab[coord.y][coord.x].pos),
					new, sizeof(t_vector));
			if (is_displayable(*new))
				ft_lstadd(&lst, ft_lstnew(&coord, sizeof(t_tupple)));
			free(new);
			coord.x++;
		}
		coord.y++;
	}
	return (lst);
}

void			fill_identity_matrix(t_matrix_four *dest)
{
	int	i;

	ft_bzero(dest, sizeof(t_matrix_four));
	i = -1;
	while (++i < 4)
		(*dest)[i][i] = 1;
}
