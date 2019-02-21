/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 17:11:33 by mrandou           #+#    #+#             */
/*   Updated: 2019/02/21 19:12:43 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_buff_history(struct s_le *le_struct)
{
	if (!le_struct->history_activ)
		while (le_struct->history->prev)
			le_struct->history = le_struct->history->prev;
	if (le_struct->term == LE_ARROW_UP\
	&& (!le_struct->nb_char || le_struct->history_activ))
		if (le_buff_history_forward(le_struct))
			return (LE_FAILURE);
	if (le_struct->term == LE_ARROW_DOWN\
	&& (!le_struct->nb_char || le_struct->history_activ))
		if (le_buff_history_backward(le_struct))
			return (LE_FAILURE);
	return (LE_SUCCESS);
}

/*
**	Test and call functions for browse the historic whit up/down arrows
*/

int		le_buff_history_forward(struct s_le *le_struct)
{
	int len;

	ft_bzero(le_struct->buff, le_struct->nb_char);
	len = ft_strlen(le_struct->history->content);
	if (!(le_struct->buff = le_buff_realloc(le_struct, len)))
		return (LE_FAILURE);
	ft_strcpy(le_struct->buff, le_struct->history->content);
	le_struct->nb_char = len;
	if (le_window_clear(le_struct))
		return (LE_FAILURE);
	le_struct->cursor_x = le_struct->nb_char + le_struct->prompt_size;
	if (le_struct->history->next)
		le_struct->history = le_struct->history->next;
	le_struct->history_activ = 1;
	return (LE_SUCCESS);
}

/*
**	Browse the historic in forward
*/

int		le_buff_history_backward(struct s_le *le_struct)
{
	int	len;

	if (le_struct->history->prev)
		le_struct->history = le_struct->history->prev;
	else
	{
		ft_bzero(le_struct->buff, le_struct->nb_char);
		if (le_window_clear(le_struct))
			return (LE_FAILURE);
		le_struct->cursor_x = le_struct->prompt_size;
		le_struct->nb_char = 0;
		le_struct->history_activ = 1;
		return (LE_SUCCESS);
	}
	ft_bzero(le_struct->buff, le_struct->nb_char);
	len = ft_strlen(le_struct->history->content);
	if (!(le_struct->buff = le_buff_realloc(le_struct, len)))
		return (LE_FAILURE);
	ft_strcpy(le_struct->buff, le_struct->history->content);
	le_struct->nb_char = len;
	if (le_window_clear(le_struct))
		return (LE_FAILURE);
	le_struct->cursor_x = le_struct->nb_char + le_struct->prompt_size;
	le_struct->history_activ = 1;
	return (LE_SUCCESS);
}

/*
**	Browse the historic in backward
**	If it's the end of the list, dump the command line
*/

void	le_buff_print(struct s_le *le_struct, int pos)
{
	if (!le_struct->buff)
		return ;
	if (le_struct->nb_char > le_struct->max_size)
	{
		ft_strclr(&le_struct->buff[le_struct->max_size]);
		le_struct->nb_char = le_struct->max_size - 1;
		le_struct->cursor_x = le_struct->nb_char + le_struct->prompt_size;
	}
	le_buff_print_select(le_struct,\
	pos, le_struct->copy_on, le_struct->copy_off);
}

/*
**	Check if the shell window can receve all chars of the buffer, or delete
**	surplus, after print
*/

void	le_buff_print_select(struct s_le *le_struct, int pos, int on, int off)
{
	int tmp;

	if (off == LE_START)
		off = le_struct->cursor_buff;
	if (off < on)
	{
		tmp = on;
		on = off;
		off = tmp;
	}
	while (le_struct->buff[pos])
	{
		if (on != LE_START && pos >= on && pos <= off)
		{
			ft_putstr(LE_SELECT_ON);
			if (le_struct->cursor_buff == pos)
				ft_putstr(LE_PROMPT_CLR);
			ft_putchar(le_struct->buff[pos]);
			ft_putstr(LE_TERM_OFF);
		}
		else
			ft_putchar(le_struct->buff[pos]);
		pos++;
	}
}

/*
**	If the select mode is activate, print the buffer with invert colors
**	for the select area. Else print char by char
*/
