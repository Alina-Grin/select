#include "ft_select.h"

static void	terminate_selection(void)
{
	leave_tty();
	free_catalog();
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
}

void		process_signals(int sig)
{
	if (sig == SIGWINCH)
		print_column();
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
