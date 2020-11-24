#include "ft_select.h"

int		ft_get_maxlen(void)
{
	int		len;
	t_args	*tmp;
	int		max;
	t_args	*start;

	tmp = g_select.g_series_args;
	start = tmp;
	max = 0;
	while (tmp)
	{
		len = ft_strlen(tmp->name);
		max = ((len > max) ? len : max);
		if (tmp->next == start)
			break ;
		tmp = tmp->next;
	}
	return (max + 1);
}

void	leave_tty(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_select.terminal.def_attr);
	tputs(g_select.terminal.ve, 1, put);
	tputs(g_select.terminal.te, 1, put);
}

int		put(int c)
{
	// return(write(g_fd, &c, 1));
	return(write(g_select.terminal.fd, &c, 1));
}

// int		count_col(void)
// {
// 	int				count_col;

// 	count_col = g_cols / (g_max + 1);
// 	return (count_col);
// }

// void drawTitle (int cols)
// {
// 	int		n;
// 	int		length;
// 	char	*title;
// 	char	*so;
// 	char	*se;
	
// 	length = ft_strlen(title);
// 	title = "(SPACE) to select, (I) to inverse selection, (ESC) to quit, (ENTER) to return selections";
// 	gotoXY (0, y);
// 	if (so = tgetstr("so", 0))
// 		tputs (so, 1, put);
// 	n = -1;
// 	while (++n < (cols - length) / 2)
// 		tputs(" ", 1, put);
// 	tputs(title, 1, put);
// 	n += length;
// 	while (n++ < cols - 1)
// 		tputs(" ", 1, put);
// 	if (se = tgetstr("se", 0))
// 		tputs (se, 1, put);
// }