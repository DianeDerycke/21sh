/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_cursor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:37:17 by mrandou           #+#    #+#             */
/*   Updated: 2019/02/21 18:58:41 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_cursor_word_forward(struct s_le *le_struct)
{
	int	i;

	i = le_struct->cursor_buff;
	if (le_struct->buff && le_struct->buff[i] == ' ')
		while (le_struct->buff && le_struct->nb_char\
		&& le_struct->buff[i] == ' ' && i <= le_struct->nb_char)
			i++;
	else
		while (le_struct->buff && le_struct->nb_char\
		&& le_struct->buff[i] != ' ' && i <= le_struct->nb_char)
			i++;
	while (le_struct->buff && le_struct->nb_char\
	&& le_struct->buff[i] == ' ' && i <= le_struct->nb_char)
		i++;
	if (le_struct->buff && le_struct->buff[i])
	{
		if (le_cursor_goto(i + le_struct->prompt_size,\
		le_struct->cursor_x, le_struct))
			return (LE_FAILURE);
		le_struct->cursor_x = i + le_struct->prompt_size;
	}
	return (LE_SUCCESS);
}

/*
**	Move the cursor forward, word by word.
*/

int		le_cursor_word_backward(struct s_le *le_struct)
{
	int	i;

	i = le_struct->cursor_buff;
	if (le_struct->buff[i] == ' ')
		while (le_struct->buff && le_struct->nb_char && le_struct->buff[i]\
		== ' ' && i <= le_struct->nb_char && i >= le_struct->prompt_size)
			i--;
	else
		while (le_struct->buff && le_struct->nb_char\
		&& le_struct->buff[i] != ' ' && i <= le_struct->nb_char)
			i--;
	while (le_struct->buff && le_struct->nb_char\
	&& le_struct->buff[i] == ' ' && i <= le_struct->nb_char)
		i--;
	if (i >= 0)
	{
		if (le_cursor_goto(i + le_struct->prompt_size,\
		le_struct->cursor_x, le_struct))
			return (LE_FAILURE);
		le_struct->cursor_x = i + le_struct->prompt_size;
	}
	return (LE_SUCCESS);
}

/*
**	Move the cursor backward, word by word.
*/

int		le_cursor_home_end(struct s_le *le_struct, int direction)
{
	if (direction == LE_HOME)
	{
		if (le_cursor_goto(le_struct->prompt_size,\
		le_struct->cursor_x, le_struct))
			return (LE_FAILURE);
		le_struct->cursor_x = le_struct->prompt_size;
	}
	if (direction == LE_END && le_struct->cursor_buff < le_struct->nb_char)
	{
		if (le_cursor_goto(le_struct->nb_char + le_struct->prompt_size,\
		le_struct->cursor_x, le_struct))
			return (LE_FAILURE);
		le_struct->cursor_x = le_struct->nb_char + le_struct->prompt_size;
	}
	return (LE_SUCCESS);
}

/*
**	Move the cursor at the beginning or the end of the command line
*/
