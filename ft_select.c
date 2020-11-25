/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeftyr <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:15:24 by szeftyr           #+#    #+#             */
/*   Updated: 2020/11/25 15:51:52 by szeftyr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		interrogate_terminal(void)
{
	g_select.terminal.ptr = g_select.terminal.buf;
	g_select.terminal.ti = tgetstr("ti", &g_select.terminal.ptr);
	g_select.terminal.te = tgetstr("te", &g_select.terminal.ptr);
	g_select.terminal.ve = tgetstr("ve", &g_select.terminal.ptr);
	g_select.terminal.vi = tgetstr("vi", &g_select.terminal.ptr);
	g_select.terminal.cl = tgetstr("cl", &g_select.terminal.ptr);
	g_select.terminal.underline = tgetstr("us", &g_select.terminal.ptr);
	g_select.terminal.reverse = tgetstr("mr", &g_select.terminal.ptr);
	g_select.terminal.norm = tgetstr("me", &g_select.terminal.ptr);
}

void		init_tty(void)
{
	int		res;

	g_select.terminal.fd = open(ttyname(STDIN_FILENO), O_RDWR | O_NOCTTY);
	if (!(g_select.terminal.tty_name = getenv("TERM")))
		print_error("Could not find the terminal name.\n");
	if (!isatty(g_select.terminal.fd))
		print_error("should be run in a terminal\n");
	res = tgetent(NULL, g_select.terminal.tty_name);
	if (res < 0)
		print_error("Could not access the termcap data base.\n");
	if (!res)
		print_error("Have not an entry to data base.\n");
	interrogate_terminal();
	tcgetattr(STDIN_FILENO, &g_select.terminal.def_attr);
	tcgetattr(g_select.terminal.fd, &g_select.terminal.attr);
	g_select.terminal.attr.c_lflag &= ~(ICANON | ECHO);
	g_select.terminal.attr.c_cc[VMIN] = 1;
	tcsetattr(g_select.terminal.fd, TCSANOW, &g_select.terminal.attr);
	tputs(g_select.terminal.ti, 1, put);
	tputs(g_select.terminal.vi, 1, put);
}

void		ft_select(void)
{
	int	key;
	int	cols;

	while (1)
	{
		cols = print_column();
		printfooter();
		key = 0;
		read(STDIN_FILENO, &key, sizeof(key));
		if (get_key(key, cols))
			break ;
	}
}

int			main(int ac, char **av)
{
	if (ac < 2)
	{
		ft_putstr_fd("You need to specify args.\n", STDERR_FILENO);
		return (0);
	}
	init_tty();
	handle_signals();
	g_select.count = ac - 1;
	create_list_args(&av[1]);
	ft_select();
	leave_tty();
	print_selected();
	free_list_args();
	return (0);
}
