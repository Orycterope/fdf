#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"
#include "matrix.h"
#define IS_DECIMAL_CHAR(c) (c >= '0' && c <= '9')

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
	//new = ft_lstnew(line, ft_strlen(line));
	new = ft_lstnew_nocpy(ft_strsplit(line, ' '), 0);
	if (new == NULL)
		return (-1);
	ft_lstappend(lst, new);
	return (length);
}

static void		fill_grid(t_grid *grid, t_list *lst)
{
	int		line;
	int		col;
	t_list	*next;
	char	**tab;
	float	z;

	line = -1;
	while (++line < grid->height)
	{
		tab = (char**)lst->content;
		col = -1;
		while (++col < grid->width)
		{
			z = (float)ft_atoi(tab[col]) / 10;
			fill_vector(&(grid->tab[line][col]), 
				col - grid->width / 2, line - grid->height / 2, z);
			free(tab[col]);
			grid->max_height = z > grid->max_height ? z : grid->max_height;
			grid->min_height = z < grid->min_height ? z : grid->min_height;
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
	t_vector	**tab;
	int			i;

	line_nbr = ft_lstlen(lst);
	tab = (t_vector**)ft_memalloc(sizeof(t_vector*) * line_nbr);
	i = 0;
	while (i < line_nbr)
		tab[i++] = (t_vector*)ft_memalloc(sizeof(t_vector) * line_length);
	grid = (t_grid*)ft_memalloc(sizeof(t_grid));
	grid->height = line_nbr;
	grid->width = line_length;
	grid->tab = tab;
	fill_grid(grid, lst);
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
	if (line_length == -1)
		return (NULL);
	return (create_grid(lst, line_length));
}
