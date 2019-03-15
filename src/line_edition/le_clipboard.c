/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_clipboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 13:09:48 by mrandou           #+#    #+#             */
/*   Updated: 2019/03/15 16:23:14 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_clipboard(struct s_le *le_struct)
{
	if (le_struct->term == LE_COPY && le_struct->nb_char)
	{
		if (le_struct->copy_on > LE_START && le_struct->copy_off > LE_START)
		{
			le_struct->copy_on = LE_START;
			le_struct->copy_off = LE_START;
		}
		if (le_clipboard_copy(le_struct))
			return (LE_FAILURE);
	}
	if (le_clipboard_exec_cut(le_struct))
		return (LE_FAILURE);
	if (le_struct->term == LE_PASTE && le_struct->clipboard)
		if (le_clipboard_paste(le_struct))
			return (LE_FAILURE);
	return (LE_SUCCESS);
}

/*
**	Call the clipboard functions and set the good values
**	for the cursor and nb_char
*/

int		le_clipboard_copy(struct s_le *le_struct)
{
	int	tmp;

	if (le_struct->copy_on == LE_START)
		le_struct->copy_on = le_struct->cursor_buff;
	else if (le_struct->copy_off == LE_START)
	{
		le_struct->copy_off = le_struct->cursor_buff;
		if (le_struct->copy_off < le_struct->copy_on)
		{
			tmp = le_struct->copy_off;
			le_struct->copy_off = le_struct->copy_on;
			le_struct->copy_on = tmp;
		}
		tmp = (le_struct->copy_off - le_struct->copy_on) + 1;
		ft_strdel(&le_struct->clipboard);
		if (!(le_struct->clipboard = ft_strndup(le_struct->buff
		+ le_struct->copy_on, tmp)))
			return (LE_FAILURE);
		le_struct->clipboard[tmp] = '\0';
	}
	return (LE_SUCCESS);
}

/*
**	Copy a part of the command line, for use: enter on select mode with
**	control + y, and select the end of your copy by press a last time
**	control + y, now this part of command are save on the clipboard
*/

int		le_clipboard_paste(struct s_le *le_struct)
{
	int len;

	len = ft_strlen(le_struct->clipboard);
	if (len + le_struct->nb_char > le_struct->max_size || !len)
		return (LE_SUCCESS);
	if (le_buff_check_space(le_struct, len) == LE_REALLOC)
		if (le_buff_realloc(le_struct, len))
			return (LE_FAILURE);
	if (!(le_struct->buff = sh_strinsert(le_struct->buff,
	le_struct->clipboard, le_struct->cursor_buff)))
		return (LE_FAILURE);
	le_struct->cursor_buff += len;
	le_struct->nb_char += len;
	le_struct->cursor_x += len;
	ft_putstr(le_struct->clipboard);
	if (le_struct->cursor_buff != le_struct->nb_char)
		if (le_window_clear_restore(le_struct))
			return (LE_FAILURE);
	return (LE_SUCCESS);
}

/*
**	Paste the clipboard content on the command line, for use: press control + p
*/

int		le_clipboard_cut(struct s_le *le_struct)
{
	int	i;
	int	k;
	int	size;

	k = 1;
	if (le_struct->copy_on == LE_START)
		le_struct->copy_on = le_struct->cursor_buff;
	if (le_clipboard_copy(le_struct))
		return (LE_FAILURE);
	i = le_struct->copy_on;
	size = ft_strlen((le_struct->buff + le_struct->copy_off) - 1);
	while (le_struct->buff[i] && k < size)
		le_struct->buff[i++] = le_struct->buff[le_struct->copy_off + k++];
	ft_strclr(le_struct->buff + i);
	return (LE_SUCCESS);
}

/*
**	Cut a part of the command line, and save the content on the clipboard
**	for use: enter on the select mode with control + y, and chose the second
**	place for cut, press control + u or delete key
*/

int		le_clipboard_exec_cut(struct s_le *le_struct)
{
	if (le_struct->term == LE_CUT && le_struct->nb_char
	&& (le_struct->copy_on != LE_START && le_struct->cursor_buff
	<= le_struct->nb_char))
	{
		if (le_clipboard_cut(le_struct))
			return (LE_FAILURE);
		le_struct->nb_char -= (ft_strlen(le_struct->clipboard));
		le_struct->cursor_buff = le_struct->cursor_x - le_struct->prompt_size;
		if (le_window_clear(le_struct))
			return (LE_FAILURE);
		if (le_cursor_beggin(le_struct, le_struct->nb_char \
		+ le_struct->prompt_size - 1))
			return (LE_FAILURE);
		if (le_struct->cursor_buff > le_struct->copy_on)
			le_struct->cursor_x = le_struct->copy_on + le_struct->prompt_size;
		if (le_cursor_restore(le_struct))
			return (LE_FAILURE);
		le_struct->copy_on = LE_START;
		le_struct->copy_off = LE_START;
	}
	return (LE_SUCCESS);
}

/*
**	Execute the cut function and set the values for the cursor and nb_char
*/
