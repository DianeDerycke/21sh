/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_termcap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 18:35:30 by mrandou           #+#    #+#             */
/*   Updated: 2019/01/22 15:38:56 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/lineedition.h"

int		le_termcap_check(char tmp[])
{
	if (tmp[0] == TC_DEL)
		return (LE_DEL);
	if (tmp[0] == LE_ESCAPE)
	{
		if (read(STDIN_FILENO, &tmp[1], 15) == -1)
			return (LE_FAILURE);
	}
	else
		return (0);
	if (!ft_strcmp(tmp, TC_HOME))
		return (LE_HOME);
	if (!ft_strcmp(tmp, TC_END))
		return (LE_END);
	if (!ft_strcmp(tmp, TC_SH_RIGHT))
		return (LE_SHIFT_RIGHT);
	if (!ft_strcmp(tmp, TC_SH_LEFT))
		return (LE_SHIFT_LEFT);
	if (!ft_strcmp(tmp, TC_SH_UP))
		return (LE_SHIFT_UP);
	if (!ft_strcmp(tmp, TC_SH_DOWN))
		return (LE_SHIFT_DOWN);
	if (!ft_strcmp(tmp, TC_UP))
		return (LE_ARROW_UP);
	if (!ft_strcmp(tmp, TC_DOWN))
		return (LE_ARROW_DOWN);
	if (!ft_strcmp(tmp, TC_RIGHT))
		return (LE_ARROW_RIGHT);
	if (!ft_strcmp(tmp, TC_LEFT))
		return (LE_ARROW_LEFT);
	if (!ft_strcmp(tmp, TC_DELFRONT))
		return (LE_DELFRONT);
	return (LE_FAILURE);
}

/*
**	Check if the char is the begginning of a termcaps
**	If it's true, reads again for get the complete termcap and see the type
*/

int		le_termcap_exec(struct s_le *le_struct)
{
	if (le_struct->term == LE_ARROW_RIGHT && le_struct->cursor_real < le_struct->nb_char)
		if (le_cursor_motion(le_struct, LE_ARROW_RIGHT))
			return (LE_FAILURE);
	if (le_struct->term == LE_ARROW_LEFT && le_struct->cursor_x > le_struct->prompt_size)
		if (le_cursor_motion(le_struct, LE_ARROW_LEFT))
			return (LE_FAILURE);
	if (le_struct->term == LE_DELFRONT && le_struct->cursor_real < le_struct->nb_char)
	{
		if (le_buff_remove(le_struct, le_struct->cursor_real))
			return (LE_FAILURE);
		if (le_termcap_print(TC_DELETE_CHAR, 1))
			return (LE_FAILURE);
		le_struct->nb_char -= 1;
	}
	if (le_struct->term == LE_DEL && le_struct->cursor_x >\
	 le_struct->prompt_size && le_struct->nb_char)
	{
		if (le_cursor_motion(le_struct, LE_ARROW_LEFT))
			return (LE_FAILURE);
		if (le_buff_remove(le_struct, le_struct->cursor_real))
			return (LE_FAILURE);
		if (le_termcap_print(TC_DELETE_CHAR, 1))
			return (LE_FAILURE);
		le_struct->nb_char -= 1;
	}
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
	if (le_struct->term == LE_ARROW_UP || le_struct->term == LE_ARROW_DOWN)
	{
		if (le_buff_history(le_struct))
			return (LE_FAILURE);
	}
	else
		le_struct->history_activ = 0;	
	return (LE_SUCCESS);
}

/*
**	Detect the termcap and execute it
*/
