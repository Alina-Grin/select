#include "ft_select.h"

void	handle_errors(char *description)
{
	ft_putstr_fd("ft_select: ", STDERR_FILENO);
	ft_putstr_fd(description, STDERR_FILENO);
	leave_tty();
	exit(EXIT_FAILURE);
}
