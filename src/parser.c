/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 17:52:31 by tvermeil          #+#    #+#             */
/*   Updated: 2017/09/12 15:42:27 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"
#include "matrix.h"
#define IS_DECIMAL_CHAR(c) (c >= '0' && c <= '9')

extern float	g_max_height;
extern float	g_min_height;

static int		is_number(char **c)
{
	int		is_left;

	is_left = 1;
	while (**c && **c != ' ')
	{
		if (**c == '-')
		{
			if (!is_left || !IS_DECIMAL_CHAR((*c)[1]))
				return (0);
		}
		else if (!IS_DECIMAL_CHAR(**c))
			return (0);
		is_left = 0;
		(*c)++;
	}
	return (is_left == 0);
}

static int		save_line(t_list **lst, char *line, int *expected_length)
{
	t_list	*new;
	char	*c;
	int		length;

	length = 0;
	c = line;
	while (*c == ' ')
		c++;
	while (*c)
	{
		if (is_number(&c) == 0)
			return (-1);
		while (*c == ' ')
			c++;
		length++;
	}
	if (*expected_length == -1)
		*expected_length = length;
	else if (length != *expected_length)
		return (-1);
	new = ft_lstnew_nocpy(ft_strsplit(line, ' '), 0);
	if (new == NULL)
		return (-1);
	ft_lstappend(lst, new);
	return (length);
}

static void		fill_grid(t_grid *grid, t_list *lst, float z)
{
	int		line;
	int		col;
	t_list	*next;
	char	**tab;

	line = -1;
	while (++line < grid->height)
	{
		tab = (char**)lst->content;
		col = -1;
		while (++col < grid->width)
		{
			z = (float)ft_atoi(tab[col]) / 10;
			fill_vector(&(grid->tab[line][col].pos),
				col - grid->width / 2, line - grid->height / 2, z);
			grid->tab[line][col].height = z;
			free(tab[col]);
			g_max_height = z > g_max_height ? z : g_max_height;
			g_min_height = z < g_min_height ? z : g_min_height;
		}
		next = lst->next;
		free(lst->content);
		free(lst);
		lst = next;
	}
}

static t_grid	*create_grid(t_list *lst, int line_length)
{
	int			line_nbr;
	t_grid		*grid;
	t_vertex	**tab;
	int			i;

	line_nbr = ft_lstlen(lst);
	tab = (t_vertex**)ft_memalloc(sizeof(t_vertex*) * line_nbr);
	i = 0;
	while (i < line_nbr)
		tab[i++] = (t_vertex*)ft_memalloc(sizeof(t_vertex) * line_length);
	grid = (t_grid*)ft_memalloc(sizeof(t_grid));
	grid->height = line_nbr;
	grid->width = line_length;
	grid->tab = tab;
	fill_grid(grid, lst, 0);
	return (grid);
}

t_grid			*parse_file(int fd)
{
	char	*line;
	t_list	*lst;
	int		line_length;

	line_length = -1;
	lst = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (save_line(&lst, line, &line_length) == -1)
			return (NULL);
		free(line);
	}
	free(line);
	if (line_length == -1)
		return (NULL);
	return (create_grid(lst, line_length));
}
