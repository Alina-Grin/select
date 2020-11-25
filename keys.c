/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szeftyr <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:15:22 by szeftyr           #+#    #+#             */
/*   Updated: 2020/11/25 11:16:42 by szeftyr          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	erase_elem(void)
{
	t_args	*tmp;

	if (!g_select.current)
		return ;
	tmp = *g_select.current;
	if (tmp == g_select.g_series_args && tmp->next == tmp)
		process_signals(SIGQUIT);
	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;
	if (tmp == g_select.g_series_args)
		g_select.g_series_args = g_select.g_series_args->next;
	g_select.count--;
	free(tmp);
}

static void	reverse_selection(void)
{
	t_args	*tmp;

	tmp = g_select.g_series_args->next;
	while (tmp)
	{
		tmp->selected = !tmp->selected;
		if (tmp == g_select.g_series_args)
			break ;
		tmp = tmp->next;
	}
}

static void	go_up(int cols)
{
	int		i;
	t_args	*tmp;

	i = 0;
	tmp = *g_select.current;
	if (tmp == g_select.g_series_args)
		return ;
	while (++i < cols)
	{
		if (tmp->prev == g_select.g_series_args)
			return ;
		tmp = tmp->prev;
	}
	if (tmp->next != g_select.g_series_args)
		g_select.current = &tmp->prev;
}

static void	go_down(int cols)
{
	int		i;
	t_args	*tmp;

	i = 0;
	tmp = *g_select.current;
	while (++i < cols)
	{
		if (tmp->next == g_select.g_series_args)
			return ;
		tmp = tmp->next;
	}
	if (tmp->next != g_select.g_series_args)
		g_select.current = &tmp->next;
}

int			get_key(int key, int columns)
{
	if (key == QUIT)
		process_signals(SIGQUIT);
	else if (key == SELECT)
	{
		(*g_select.current)->selected = !(*g_select.current)->selected;
		g_select.current = &(*g_select.current)->next;
	}
	else if (key == INVERSE)
		reverse_selection();
	else if (key == RIGHT)
		g_select.current = &(*g_select.current)->next;
	else if (key == LEFT)
		g_select.current = &(*g_select.current)->prev;
	else if (key == DOWN)
		go_down(columns);
	else if (key == UP)
		go_up(columns);
	else if (key == RETURN)
		return (1);
	else if (key == BACKSPACE || key == DELETE)
		erase_elem();
	return (0);
}
