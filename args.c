#include "ft_select.h"

void			free_catalog(void)
{
	t_args	*curs;
	t_args	*tmp;

	curs = g_select.g_series_args;
	while (curs)
	{
		tmp = curs;
		if (tmp->prev)
			tmp->prev->next = NULL;
		if (tmp->next)
			tmp->next->prev = tmp->prev;
		curs = curs->next;
		tmp->prev = NULL;
		tmp->next = NULL;
		free(tmp);
		tmp = NULL;
	}
}

static t_args	*create_new_el(char *name)
{
	t_args	*newel;
	struct stat buf;

	if (!(newel = (t_args *)malloc(sizeof(t_args))))
	if (newel == NULL)
	{
		ft_putstr_fd("ft_select: Can not allocate memory.\n", STDERR_FILENO);
		leave_tty();
		exit(EXIT_FAILURE);
	}
	newel->name = name;
	newel->prev = newel;
	newel->next = newel;
	newel->selected = false;
	if (!lstat(name, &buf))
		newel->type = buf.st_mode;
	else
		newel->type = 0;
	return (newel);
}

void			fill_catalog(char **av)
{
	t_args		*newel;

	while (*av)
	{
		newel = create_new_el(*av);
		if (!g_select.g_series_args)
			g_select.g_series_args = newel;
		g_select.g_series_args->prev->next = newel;
		newel->next = g_select.g_series_args;
		newel->prev = g_select.g_series_args->prev;
		g_select.g_series_args->prev = newel;
		av++;
	}
	if (g_select.g_series_args)
		g_select.current = &g_select.g_series_args;
}
