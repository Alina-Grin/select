/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeftyr <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:15:30 by szeftyr           #+#    #+#             */
/*   Updated: 2020/11/25 15:52:09 by szeftyr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft/libft.h"
# include <termios.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <termcap.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>

# define D_COLOR				"\033[38;5;37m"
# define F_COLOR				"\033[38;5;150m"
# define B_COLOR				"\033[38;5;209m"
# define OTH_COLOR				"\033[38;5;109m"
# define DEFAULT_COLOR			"\033[0m"
# define SELECTED				"\033[07m"
# define UNDERLINED				"\033[04m"

# define RETURN					10
# define QUIT					27
# define SELECT					32
# define INVERSE				105
# define BACKSPACE				127
# define DELETE					2117294875
# define UP						4283163
# define DOWN					4348699
# define RIGHT					4414235
# define LEFT					4479771

typedef struct					s_args
{
	mode_t						type;
	char						*name;
	bool						selected;
	struct s_args				*prev;
	struct s_args				*next;
}								t_args;

typedef struct					s_term
{
	char						buf[512];
	struct termios				def_attr;
	struct termios				attr;
	int							fd;
	char						*ptr;
	char						*tty_name;
	char						*te;
	char						*ti;
	char						*ve;
	char						*vi;
	char						*cl;
	char						*underline;
	char						*reverse;
	char						*norm;
}								t_term;

typedef struct					s_config
{
	t_term						terminal;
	t_args						**current;
	t_args						*g_series_args;
	int							count;
}								t_config;

t_config						g_select;

void							print_error(char *msg);
void							init_tty(void);
void							leave_tty(void);
int								put(int n);
void							handle_signals(void);
void							process_signals(int signo);
void							create_list_args(char **av);
void							free_list_args(void);
void							ft_select(void);
int								ft_get_maxlen(void);
int								print_column(void);
void							print_selected(void);
int								get_key(int key, int columns);
void							printfooter(void);

#endif
