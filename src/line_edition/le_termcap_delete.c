/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_termcap_delete.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 15:53:38 by mrandou           #+#    #+#             */
/*   Updated: 2019/03/16 15:53:49 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_termcap_delete(struct s_le *le_struct)
{
	if (le_termcap_del_cut(le_struct))
		return (LE_FAILURE);
	if (le_struct->term == LE_DEL\
	&& le_struct->cursor_x > le_struct->prompt_size && le_struct->nb_char)
	{
		if (le_cursor_motion(le_struct, LE_ARROW_LEFT))
			return (LE_FAILURE);
		le_struct->cursor_buff--;
		if (le_buff_remove(le_struct, le_struct->cursor_buff))
			return (LE_FAILURE);
		if (le_struct->cursor_buff != le_struct->nb_char)
		{
			if (le_window_clear_restore(le_struct))
				return (LE_FAILURE);
		}
		else
		{
			if (le_termcap_print(TC_DELETE_CHAR, 1))
				return (LE_FAILURE);
		}
	}
	return (LE_SUCCESS);
}

int		le_termcap_del_cut(struct s_le *le_struct)
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
		if (le_struct->cursor_buff != le_struct->nb_char)
			if (le_window_clear_restore(le_struct))
				return (LE_FAILURE);
		if (le_struct->cursor_buff == le_struct->nb_char)
			if (le_termcap_print(TC_DELETE_CHAR, 1))
				return (LE_FAILURE);
		le_struct->term = 0;
	}
	return (LE_SUCCESS);
}

/*
**	Test the removal posibility, and call the delete functions
**	For a feature, it's possible to delete a part of the command line
**	with the select mode and by press delete key
*/
