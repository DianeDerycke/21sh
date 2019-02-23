/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:32:12 by mrandou           #+#    #+#             */
/*   Updated: 2019/02/23 13:46:01 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_window_size(int *col, int *line)
{
	if (le_termcap_init())
		return (LE_FAILURE);
	if ((*col = tgetnum(TC_GET_COL)) == -1)
		return (LE_FAILURE);
	if ((*line = tgetnum(TC_GET_LINE)) == -1)
		return (LE_FAILURE);
	if (*col <= 0 || *line <= 0)
		return (LE_FAILURE);
	return (LE_SUCCESS);
}

/*
**	Get the size of the shell window
*/

int		le_window_check(struct s_le *le_struct)
{
	int	col_new;
	int	line_new;

	if (!le_struct->w_col || !le_struct->w_line)
		return (LE_FAILURE);
	if (le_window_size(&col_new, &line_new))
		return (LE_FAILURE);
	if (le_struct->w_col != col_new || le_struct->w_line != line_new)
	{
		le_struct->w_col = col_new;
		le_struct->w_line = line_new;
		le_struct->max_size = col_new * line_new - le_struct->prompt_size;
		if (le_window_clear_all_restore(le_struct))
			return (LE_FAILURE);
	}
	return (LE_SUCCESS);
}

/*
**	Check if the window was resize, if it's true, clear and print
**	Restore cursor position
*/

int		le_window_clear(struct s_le *le_struct)
{
	if (le_cursor_beggin(le_struct, le_struct->cursor_x))
		return (LE_FAILURE);
	if (le_termcap_print(TC_CLEAR_NEXT, 1))
		return (LE_FAILURE);
	le_prompt_print(le_struct);
	le_buff_print(le_struct, 0);
	return (LE_SUCCESS);
}

/*
**	Clear and reprint the prompt and the buffer
*/

int		le_window_clear_restore(struct s_le *le_struct)
{
	if (le_window_clear(le_struct))
		return (LE_FAILURE);
	if (le_cursor_beggin(le_struct, le_struct->nb_char \
	+ le_struct->prompt_size - 1))
		return (LE_FAILURE);
	if (le_cursor_restore(le_struct))
		return (LE_FAILURE);
	return (LE_SUCCESS);
}

/*
**	Clear and reprint the prompt and the buffer, restore the cursor position
*/

int		le_window_clear_all_restore(struct s_le *le_struct)
{
	if (le_termcap_print(TC_CLEAR, 1))
		return (LE_FAILURE);
	le_prompt_print(le_struct);
	le_buff_print(le_struct, 0);
	if (le_cursor_beggin(le_struct, le_struct->nb_char \
	+ le_struct->prompt_size - 1))
		return (LE_FAILURE);
	if (le_cursor_restore(le_struct))
		return (LE_FAILURE);
	return (LE_SUCCESS);
}

/*
**	Clear the window and reprint the prompt and the buffer
**	Restore the cursor position
*/
