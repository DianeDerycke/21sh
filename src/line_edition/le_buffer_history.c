/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_buffer_history.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:33:08 by mrandou           #+#    #+#             */
/*   Updated: 2019/03/02 17:05:30 by mrandou          ###   ########.fr       */
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

	len = ft_strlen(le_struct->history->content);
	if (le_buff_check_space(le_struct, len) == LE_REALLOC)
		if (le_buff_realloc(le_struct, len))
			return (LE_FAILURE);
	ft_bzero(le_struct->buff, le_struct->nb_char + 1);
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
		if (le_buff_history_clear(le_struct))
			return (LE_FAILURE);
		return (LE_SUCCESS);
	}
	len = ft_strlen(le_struct->history->content);\
	if (le_buff_check_space(le_struct, len) == LE_REALLOC)
		if (le_buff_realloc(le_struct, len))
			return (LE_FAILURE);
	ft_bzero(le_struct->buff, le_struct->nb_char + 1);
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

int		le_buff_history_clear(struct s_le *le_struct)
{
	ft_bzero(le_struct->buff, le_struct->nb_char);
	if (le_window_clear(le_struct))
		return (LE_FAILURE);
	le_struct->cursor_x = le_struct->prompt_size;
	le_struct->nb_char = 0;
	le_struct->history_activ = 1;
	return (LE_SUCCESS);
}

/*
**	Use when this is the beginning of the history list
**	clear the actual history command line
*/
