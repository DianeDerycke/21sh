/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_cursor_tool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 18:52:41 by mrandou           #+#    #+#             */
/*   Updated: 2019/02/21 18:59:16 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_cursor_goto(int expected, int current, struct s_le *le_struct)
{
	int	diff;

	diff = current - expected;
	expected = (expected - 1) / le_struct->w_col;
	current = (current - 1) / le_struct->w_col;
	expected = expected - current;
	if (expected > 0)
		le_ansi_print(expected, LE_DOWN);
	else if (expected < 0)
	{
		expected *= -1;
		le_ansi_print(expected, LE_UP);
	}
	if (diff < 0)
		diff = -diff - (le_struct->w_col * expected);
	else if (diff > 0)
		diff = (le_struct->w_col * expected) - diff;
	if (diff > 0)
		le_ansi_print(diff, LE_RIGHT);
	if (diff < 0)
		le_ansi_print(diff * -1, LE_LEFT);
	return (LE_SUCCESS);
}

/*
**	Move to current position at expected
*/

int		le_cursor_restore(struct s_le *le_struct)
{
	int line;
	int col;

	line = (le_struct->cursor_x - 1) / le_struct->w_col;
	col = (le_struct->cursor_x - 1) % le_struct->w_col;
	if (line > 0)
		if (le_termcap_print(TC_GO_DOWN, line))
			return (LE_FAILURE);
	if (col)
		le_ansi_print(col, LE_RIGHT);
	return (LE_SUCCESS);
}

/*
**	Restore the cursor, the cursor must be at the beginning of the line command
*/

int		le_cursor_beggin(struct s_le *le_struct, int current)
{
	int y;

	y = ((current - 1) / le_struct->w_col);
	if (le_termcap_print(TC_GO_BEGIN, 1))
		return (LE_FAILURE);
	if (y)
		le_ansi_print(y, LE_UP);
	return (LE_SUCCESS);
}

/*
**	Put the cursor at the beginning of the command line
*/
