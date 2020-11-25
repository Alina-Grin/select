/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeftyr <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:15:12 by szeftyr           #+#    #+#             */
/*   Updated: 2020/11/25 12:12:34 by szeftyr          ###   ########.fr       */
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
