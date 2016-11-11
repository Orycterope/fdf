#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"
#include "matrix.h"
#define IS_DECIMAL_CHAR(c) (c >= '0' && c <= '9')
#define GET_BLUE(x)		(x & 0xFF)
#define GET_GREEN(x)	((x >> 8) & 0xFF)
#define GET_RED(x)		((x >> 16) & 0xFF)
#define TO_BLUE(x)		(((int)(x)) & 0xFF)
#define TO_GREEN(x)		((((int)(x)) & 0xFF) << 8)
#define TO_RED(x)		((((int)(x)) & 0xFF) << 16)


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
			fill_vector(&(grid->tab[line][col].pos),
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

static void		fill_colors(t_grid *grid)
{
	int	line;
	int	col;
	int	color;
	float relative;

	line = -1;
	while (++line < grid->height)
	{
		col = -1;
		while (++col < grid->width)
		{
			relative = (grid->tab[line][col].pos[2] - grid->min_height) \
				/ grid->max_height;
			color = TO_RED(relative * (GET_RED(HIGH_COLOR) \
					- GET_RED(LOW_COLOR)) + GET_RED(LOW_COLOR));
			color |= TO_GREEN(relative * (GET_GREEN(HIGH_COLOR) \
					- GET_GREEN(LOW_COLOR)) + GET_GREEN(LOW_COLOR));
			color |= TO_BLUE(relative * (GET_BLUE(HIGH_COLOR) \
					- GET_BLUE(LOW_COLOR)) + GET_BLUE(LOW_COLOR));
			grid->tab[line][col].color = color;
		}
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
	fill_grid(grid, lst);
	fill_colors(grid);
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
