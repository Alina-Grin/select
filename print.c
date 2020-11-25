/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeftyr <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:15:04 by szeftyr           #+#    #+#             */
/*   Updated: 2020/11/25 11:39:21 by szeftyr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	putstr_color(t_args *elem)
{
	if (S_ISDIR(elem->type))
		tputs(D_COLOR, 1, put);
	else if (S_ISREG(elem->type))
	{
		if (S_IEXEC & elem->type)
			tputs(B_COLOR, 1, put);
		else
			tputs(F_COLOR, 1, put);
	}
	else if (S_ISLNK(elem->type))
		tputs(B_COLOR, 1, put);
	else
		tputs(OTH_COLOR, 1, put);
	tputs(elem->name, 1, put);
	tputs(DEFAULT_COLOR, 1, put);
}

static void	print_elem(t_args *elem, int max_len)
{
	int				len;

	len = ft_strlen(elem->name);
	if ((*g_select.current) == elem)
		tputs(g_select.terminal.underline, 1, put);
	if (elem->selected)
		tputs(g_select.terminal.reverse, 1, put);
	putstr_color(elem);
	while (++len <= max_len)
		tputs(" ", 1, put);
}

static int	printing(t_args *elem, int max_len, int *counter, int colcount)
{
	print_elem(elem, max_len);
	(*counter)++;
	if (*counter == colcount)
	{
		tputs("\n", 1, put);
		*counter = 0;
	}
	if (elem->next == g_select.g_series_args)
	{
		tputs("\n", 1, put);
		return (1);
	}
	return (0);
}

int			print_column(void)
{
	t_args			*tmp;
	int				colcount;
	int				counter;
	int				max_len;
	struct winsize	wsize;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &wsize);
	tmp = g_select.g_series_args;
	max_len = ft_get_maxlen();
	counter = 0;
	colcount = wsize.ws_col / (max_len + 1);
	if (colcount * wsize.ws_row < g_select.count)
	{
		tputs(tgetstr("cl", 0), 1, put);
		tputs("Not enough space.\n", 1, put);
		return (0);
	}
	tputs(tgetstr("cl", 0), 1, put);
	while (tmp)
	{
		if (printing(tmp, max_len, &counter, colcount))
			break ;
		tmp = tmp->next;
	}
	return (colcount);
}

void		print_selected(void)
{
	t_args	*start;
	int		i;

	start = g_select.g_series_args;
	i = 0;
	while (start)
	{
		if (start->selected)
		{
			if (i)
				ft_putstr_fd(" ", STDOUT_FILENO);
			i = 1;
			ft_putstr_fd(start->name, STDOUT_FILENO);
		}
		start = start->next;
		if (start == g_select.g_series_args)
			break ;
	}
}
