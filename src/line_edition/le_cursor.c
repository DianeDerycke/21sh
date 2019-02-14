/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_cursor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:37:17 by mrandou           #+#    #+#             */
/*   Updated: 2019/02/14 13:39:53 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_cursor_motion(struct s_le *le_struct, int motion)
{
	if (motion == LE_ARROW_RIGHT)
	{
		// if (le_struct->buff[le_struct->cursor_x + le_struct->prompt_size + 1] == LE_ENDL)
		// {
		// 	le_termcap_print(TC_GO_DOWN, 1);
		// 	le_struct->cursor_x += 1;
		// 	le_struct->cursor_y += 1;
		// }
		// else 
			if (le_cursor_right(le_struct))
				return (LE_FAILURE);
	}
	if (motion == LE_ARROW_LEFT)
	{
		// if (le_struct->buff[le_struct->cursor_x + le_struct->prompt_size - 1] == LE_ENDL)
		// {
		// 	if (le_cursor_endl(le_struct))
		// 		return (LE_FAILURE);
		// }
		// else
			if (le_cursor_left(le_struct))
				return (LE_FAILURE);
	}
	if (motion == LE_SHIFT_UP)
		if (le_cursor_up(le_struct))
			return (LE_FAILURE);
	if (motion == LE_SHIFT_DOWN)
		if (le_cursor_down(le_struct))
			return (LE_FAILURE);
	return (LE_SUCCESS);
}

/*
**	Check and move if it's posible to move the cursor on right or left 
*/

int		le_cursor_right(struct s_le *le_struct)
{
	if (le_struct->cursor_y &&\
	 (le_struct->cursor_x / le_struct->cursor_y) == le_struct->w_col)
	{
		if (le_termcap_print(TC_GO_DOWN, 1))
			return (LE_FAILURE);
	}
	else
		if (le_termcap_print(TC_GO_RIGHT, 1))
			return (LE_FAILURE);
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
		if (le_termcap_print(TC_GO_LEFT, 1))
			return (LE_FAILURE);
	le_struct->cursor_x -= 1;
	return (LE_SUCCESS);
}

/*
**	Move the cursor to left, but if it's edge of the shell, go up
*/

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
	if (line)
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

int		le_cursor_word_forward(struct s_le *le_struct)
{
	int	i;

	i = le_struct->cursor_buff;
	if (le_struct->buff && le_struct->buff[i] == ' ')
		while (le_struct->buff && le_struct->nb_char && \
		le_struct->buff[i] == ' ' && i <= le_struct->nb_char)
			i++;
	else
		while (le_struct->buff && le_struct->nb_char && \
		le_struct->buff[i] != ' ' && i <= le_struct->nb_char)
			i++;
		while (le_struct->buff && le_struct->nb_char && \
		le_struct->buff[i] == ' ' && i <= le_struct->nb_char)
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
		while (le_struct->buff && le_struct->nb_char && \
		le_struct->buff[i] != ' ' && i <= le_struct->nb_char)
			i--;
		while (le_struct->buff && le_struct->nb_char && \
		le_struct->buff[i] == ' ' && i <= le_struct->nb_char)
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
		if (le_cursor_goto(le_struct->prompt_size, \
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
**	Move the cursor to up
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
**	Move the cursor to down
*/
