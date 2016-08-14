#ifndef FDF_H
# define FDF_H

typedef struct		s_grid
{
	int				height;
	int				width;
	int				**tab;
}					t_grid;

t_grid				*parse_file(int fd);

#endif
