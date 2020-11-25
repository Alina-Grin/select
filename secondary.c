/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeftyr <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:15:12 by szeftyr           #+#    #+#             */
/*   Updated: 2020/11/25 16:01:27 by szeftyr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	print_error(char *msg)
{
	ft_putstr_fd("ft_select: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	leave_tty();
	exit(EXIT_FAILURE);
}

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
	return (write(g_select.terminal.fd, &c, 1));
}

void	printfooter(void)
{
	int				n;
	int				length;
	char			*title;
	struct winsize	wsize;

	ioctl(STDIN_FILENO, TIOCGWINSZ, &wsize);
	title = "SPACE: select | I: inverse selection | ESC: quit | ENTER: return";
	length = ft_strlen(title);
	n = -1;
	tputs(g_select.terminal.reverse, 1, put);
	tputs(OTH_COLOR, 1, put);
	tputs("\n", 1, put);
	while (++n < (wsize.ws_col - length) / 2)
		tputs("-", 1, put);
	tputs(title, 1, put);
	n += length;
	while (n++ < wsize.ws_col)
		tputs("-", 1, put);
	tputs("\n", 1, put);
	tputs(DEFAULT_COLOR, 1, put);
}
