/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_cursor_motion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 18:47:15 by mrandou           #+#    #+#             */
/*   Updated: 2019/02/21 18:51:26 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_cursor_motion(struct s_le *le_struct, int motion)
{
	if (motion == LE_ARROW_RIGHT)
		if (le_cursor_right(le_struct))
			return (LE_FAILURE);
	if (motion == LE_ARROW_LEFT)
		if (le_cursor_left(le_struct))
			return (LE_FAILURE);
	if (motion == LE_SHIFT_UP)
		if (le_cursor_up(le_struct))
			return (LE_FAILURE);
	if (motion == LE_SHIFT_DOWN)
		if (le_cursor_down(le_struct))
			return (LE_FAILURE);
	return (LE_SUCCESS);
}

/*
**	Check and move if it's possible to move the cursor on right, left, up
**	or down
*/

int		le_cursor_right(struct s_le *le_struct)
{
	if ((le_struct->cursor_y && (le_struct->cursor_x / le_struct->cursor_y)\
	== le_struct->w_col))
	{
		if (le_termcap_print(TC_GO_DOWN, 1))
			return (LE_FAILURE);
	}
	else
	{
		if (le_termcap_print(TC_GO_RIGHT, 1))
			return (LE_FAILURE);
	}
	le_struct->cursor_x += 1;
	return (LE_SUCCESS);
}

/*
**	Move the cursor to right, but if it's edge of the shell, go down
*/

int		le_cursor_left(struct s_le *le_struct)
{
	if (le_struct->cursor_x - 1 == le_struct->w_col * (le_struct->cursor_y - 1))
	{
		if (le_termcap_print(TC_GO_UP, 1))
			return (LE_FAILURE);
		if (le_ansi_print(le_struct->w_col, LE_RIGHT))
			return (LE_FAILURE);
	}
	else
	{
		if (le_termcap_print(TC_GO_LEFT, 1))
			return (LE_FAILURE);
	}
	le_struct->cursor_x -= 1;
	return (LE_SUCCESS);
}

/*
**	Move the cursor to left, but if it's edge of the shell, go up
*/

int		le_cursor_up(struct s_le *le_struct)
{
	if (le_struct->cursor_y > 2)
	{
		if (le_cursor_goto(le_struct->cursor_x - le_struct->w_col,\
		le_struct->cursor_x, le_struct))
			return (LE_FAILURE);
		le_struct->cursor_x -= le_struct->w_col;
	}
	else if (le_struct->cursor_y == 2)
	{
		if (le_struct->cursor_x - le_struct->w_col - le_struct->prompt_size > 0)
		{
			if (le_cursor_goto(le_struct->cursor_x - le_struct->w_col,\
			le_struct->cursor_x, le_struct))
				return (LE_FAILURE);
			le_struct->cursor_x -= le_struct->w_col;
		}
		else if (le_struct->cursor_y)
		{
			if (le_cursor_goto(le_struct->prompt_size,\
			le_struct->cursor_x, le_struct))
				return (LE_FAILURE);
			le_struct->cursor_x = le_struct->prompt_size;
		}
	}
	return (LE_SUCCESS);
}

/*
**	Move the cursor to up, taking into account the size of the first line
*/

int		le_cursor_down(struct s_le *le_struct)
{
	if (le_struct->cursor_y + 1 < le_struct->nb_line)
	{
		if (le_cursor_goto(le_struct->cursor_x + le_struct->w_col,\
		le_struct->cursor_x, le_struct))
			return (LE_FAILURE);
		le_struct->cursor_x += le_struct->w_col;
	}
	else if (le_struct->cursor_y + 1 == le_struct->nb_line)
	{
		if ((le_struct->cursor_x - le_struct->w_col * le_struct->cursor_y)\
		+ le_struct->w_col > le_struct->last_line - 1)
		{
			if (le_cursor_goto(le_struct->nb_char + le_struct->prompt_size,\
			le_struct->cursor_x, le_struct))
				return (LE_FAILURE);
			le_struct->cursor_x = le_struct->nb_char + le_struct->prompt_size;
			return (LE_SUCCESS);
		}
		if (le_cursor_goto(le_struct->cursor_x + le_struct->w_col,\
		le_struct->cursor_x, le_struct))
			return (LE_FAILURE);
		le_struct->cursor_x += le_struct->w_col;
	}
	return (LE_SUCCESS);
}

/*
**	Move the cursor to down, taking into account the size of the last line
*/
