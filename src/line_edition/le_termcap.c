/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_termcap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 18:35:30 by mrandou           #+#    #+#             */
/*   Updated: 2019/03/09 15:37:23 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_termcap_check(struct s_le *le_struct)
{
	if (le_struct->tmp[0] == LE_CLEAR)
		if (le_window_clear_all_restore(le_struct))
			return (LE_FAILURE);
	if (le_struct->tmp[0] == LE_COPY)
		le_struct->term = LE_COPY;
	else if (le_struct->tmp[0] == LE_PASTE)
		le_struct->term = LE_PASTE;
	else if (le_struct->tmp[0] == LE_CUT)
		le_struct->term = LE_CUT;
	else if (le_struct->tmp[0] == TC_DEL)
		le_struct->term = LE_DEL;
	else if (le_struct->tmp[0] == LE_EOT)
		le_struct->term = LE_EOF;
	else if (le_struct->tmp[0] == LE_EXIT)
		le_struct->term = LE_ETX;
	else if (le_struct->tmp[0] == LE_ESCAPE)
	{
		if (read(STDIN_FILENO, &le_struct->tmp[1], LE_TMP_BUFF_SIZE - 1) == -1)
			return (LE_FAILURE);
		le_termcap_type(le_struct);
	}
	return (le_struct->term ? LE_SUCCESS : LE_FAILURE);
}

/*
**	Check if the char is a clipboard command or delete command
**	EOT is the End Of Transmission, when the user push control + D
**	Check if the char is the begginning of a termcaps
**	If it's true, reads again and call le_tecamp_type
**	for get the complete termcap and see the type
*/

void	le_termcap_type(struct s_le	*le_struct)
{
	if (!ft_strcmp(le_struct->tmp, TC_HOME))
		le_struct->term = LE_HOME;
	else if (!ft_strcmp(le_struct->tmp, TC_END))
		le_struct->term = LE_END;
	else if (!ft_strcmp(le_struct->tmp, TC_SH_RIGHT))
		le_struct->term = LE_SHIFT_RIGHT;
	else if (!ft_strcmp(le_struct->tmp, TC_SH_LEFT))
		le_struct->term = LE_SHIFT_LEFT;
	else if (!ft_strcmp(le_struct->tmp, TC_SH_UP))
		le_struct->term = LE_SHIFT_UP;
	else if (!ft_strcmp(le_struct->tmp, TC_SH_DOWN))
		le_struct->term = LE_SHIFT_DOWN;
	else if (!ft_strcmp(le_struct->tmp, TC_UP))
		le_struct->term = LE_ARROW_UP;
	else if (!ft_strcmp(le_struct->tmp, TC_DOWN))
		le_struct->term = LE_ARROW_DOWN;
	else if (!ft_strcmp(le_struct->tmp, TC_RIGHT))
		le_struct->term = LE_ARROW_RIGHT;
	else if (!ft_strcmp(le_struct->tmp, TC_LEFT))
		le_struct->term = LE_ARROW_LEFT;
	else if (!ft_strcmp(le_struct->tmp, TC_DELFRONT))
		le_struct->term = LE_DELFRONT;
}

/*
**	Check the termcaps type
*/

int		le_termcap_exec(struct s_le *le_struct)
{
	if (le_termcap_motion(le_struct))
		return (LE_FAILURE);
	if (le_struct->term == LE_COPY || le_struct->term == LE_CUT\
	|| le_struct->term == LE_PASTE)
		if (le_clipboard(le_struct))
			return (LE_FAILURE);
	if (le_termcap_delete(le_struct))
		return (LE_FAILURE);
	if (le_struct->history_activ != -1\
	&& (le_struct->term == LE_ARROW_UP || le_struct->term == LE_ARROW_DOWN))
	{
		if (le_buff_history(le_struct))
			return (LE_FAILURE);
	}
	else if (le_struct->history_activ != -1)
		le_struct->history_activ = 0;
	if ((le_struct->copy_on != LE_START && le_struct->copy_off == LE_START))
		if (le_window_clear_restore(le_struct))
			return (LE_FAILURE);
	return (LE_SUCCESS);
}

/*
**	Detect the termcap and execute it
*/

int		le_termcap_motion(struct s_le *le_struct)
{
	if (le_struct->term == LE_ARROW_RIGHT\
	&& le_struct->cursor_buff < le_struct->nb_char)
		if (le_cursor_motion(le_struct, LE_ARROW_RIGHT))
			return (LE_FAILURE);
	if (le_struct->term == LE_ARROW_LEFT\
	&& le_struct->cursor_x > le_struct->prompt_size)
		if (le_cursor_motion(le_struct, LE_ARROW_LEFT))
			return (LE_FAILURE);
	if (le_struct->term == LE_SHIFT_RIGHT)
		if (le_cursor_word_forward(le_struct))
			return (LE_FAILURE);
	if (le_struct->term == LE_SHIFT_LEFT)
		if (le_cursor_word_backward(le_struct))
			return (LE_FAILURE);
	if (le_struct->term == LE_END || le_struct->term == LE_HOME)
		if (le_cursor_home_end(le_struct, le_struct->term))
			return (LE_FAILURE);
	if (le_struct->term == LE_SHIFT_UP || le_struct->term == LE_SHIFT_DOWN)
		if (le_cursor_motion(le_struct, le_struct->term))
			return (LE_FAILURE);
	return (LE_SUCCESS);
}

/*
**	Test the motion posibility and call the functions for the cursor motion
*/

int		le_termcap_delete(struct s_le *le_struct)
{
	if (le_struct->copy_on != LE_START && le_struct->copy_off == LE_START\
	&& (le_struct->term == LE_DEL || le_struct->term == LE_DELFRONT))
	{
		le_struct->term = LE_CUT;
		if (le_clipboard(le_struct))
			return (LE_FAILURE);
	}
	if ((le_struct->term == LE_DELFRONT || (le_struct->term == LE_EOF
	&& le_struct->nb_char)) && le_struct->cursor_buff < le_struct->nb_char
	&& le_struct->nb_char)
	{
		if (le_buff_remove(le_struct, le_struct->cursor_buff))
			return (LE_FAILURE);
		if (le_window_clear_restore(le_struct))
			return (LE_FAILURE);
		le_struct->term = 0;
	}
	if (le_struct->term == LE_DEL\
	&& le_struct->cursor_x > le_struct->prompt_size && le_struct->nb_char)
	{
		if (le_cursor_motion(le_struct, LE_ARROW_LEFT))
			return (LE_FAILURE);
		le_struct->cursor_buff--;
		if (le_buff_remove(le_struct, le_struct->cursor_buff))
			return (LE_FAILURE);
		if (le_window_clear_restore(le_struct))
			return (LE_FAILURE);
	}
	return (LE_SUCCESS);
}

/*
**	Test the removal posibility, and call the delete functions
**	For a feature, it's possible to delete a part of the command line
**	with the select mode and by press delete key
*/
