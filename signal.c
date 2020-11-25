/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeftyr <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:15:20 by szeftyr           #+#    #+#             */
/*   Updated: 2020/11/25 15:51:57 by szeftyr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	terminate_selection(void)
{
	leave_tty();
	free_list_args();
	signal(SIGTSTP, SIG_DFL);
	exit(EXIT_SUCCESS);
}

static void	pause_selection(void)
{
	leave_tty();
	signal(SIGTSTP, SIG_DFL);
	ioctl(STDIN_FILENO, TIOCSTI, "\032");
}

static void	resume_selection(void)
{
	init_tty();
	handle_signals();
	print_column();
	printfooter();
}

void		process_signals(int sig)
{
	if (sig == SIGWINCH)
	{
		print_column();
		printfooter();
	}
	else if (sig == SIGTSTP)
		pause_selection();
	else if (sig == SIGCONT)
		resume_selection();
	else if (sig == SIGKILL || sig == SIGSTOP || sig == SIGABRT
			|| sig == SIGINT || sig == SIGQUIT)
		terminate_selection();
}

void		handle_signals(void)
{
	signal(SIGWINCH, process_signals);
	signal(SIGABRT, process_signals);
	signal(SIGINT, process_signals);
	signal(SIGSTOP, process_signals);
	signal(SIGCONT, process_signals);
	signal(SIGTSTP, process_signals);
	signal(SIGKILL, process_signals);
	signal(SIGQUIT, process_signals);
}
