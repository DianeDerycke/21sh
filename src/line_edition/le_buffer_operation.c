/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_buffer_operation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 17:47:26 by mrandou           #+#    #+#             */
/*   Updated: 2019/01/24 14:34:22 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_buff_remove(struct s_le *le_struct, int i)
{
	int	len;

	if (!le_struct->nb_char || i < 0)
		return (LE_FAILURE);
	len = ft_strlen(le_struct->buff);
	if (i > len)
		return (LE_FAILURE);
	while (le_struct->buff[i + 1])
	{
		le_struct->buff[i] = le_struct->buff[i + 1];
		i++;
	}
	le_struct->buff[i] = '\0';
	return (LE_SUCCESS);
}

/*
**	Delete a char at i position
*/

int		le_buff_add(struct s_le *le_struct, int i, char c)
{
	char	old;
	char	new;
	int		len;

	if (!c || i < 0)
		return (LE_FAILURE);
	if (!le_struct->nb_char)
	{
		le_struct->buff[0] = c;
		return (LE_SUCCESS);
	}
	if (i > (len = ft_strlen(le_struct->buff)))
		i = len;
	old = le_struct->buff[i];
	le_struct->buff[i++] = c;
	new = '\0';
	while (le_struct->buff[i])
	{
		new = le_struct->buff[i];
		le_struct->buff[i++] = old;
		old = new;
	}
	le_struct->buff[i] = old;
	le_struct->buff[i + 1] = '\0';
	return (LE_SUCCESS);
}

/*
**	Add the c char at i position on the buffer and shift all chars after i
*/


int		le_buff_append(struct s_le *le_struct, char c)
{
	if (c != LE_ENDL)
		if (le_buff_add(le_struct, le_struct->cursor_real, c))
			return (LE_FAILURE);
	if (le_struct->cursor_real != le_struct->nb_char)
	{
		if (le_termcap_print(TC_CLEAR_NEXT, 1))
			return (LE_FAILURE);
		ft_putstr(&le_struct->buff[le_struct->cursor_real]);
		// le_debug_fct(le_struct);
		if (le_cursor_restore(le_struct->cursor_real, le_struct->nb_char, le_struct))
			return (LE_FAILURE);
	}
	else
		ft_putchar(c);
	// if (*cursor == col_window * nbline)
	// 	if (le_termcap_print(TC_GO_DOWN, 1))
	// 		return (LE_FAILURE);
	le_struct->nb_char += 1;
	le_struct->cursor_x += 1;
	le_struct->history_activ = 0;
	return (LE_SUCCESS);
}

/*
**	Append the new read char to the buffer at cursor position
**	Clear at cursor position and print
**	If the cursor is at end of the line, it move down
*/

char		*le_buff_realloc(struct s_le *le_struct)
{
	char	*tmp;
	
	le_struct->buffer_size = le_struct->buffer_size + LE_BUFF_SIZE;
	if (!(tmp = ft_strdup(le_struct->buff)))
		return (NULL);
	ft_strdel(&le_struct->buff);
	if (!(le_struct->buff = (char *)malloc(sizeof(char *) * le_struct->buffer_size)))
		return (NULL);
	if (!(ft_memmove(le_struct->buff, tmp, le_struct->buffer_size)))
	{
		ft_strdel(&tmp);
		return (NULL);
	}
	ft_strdel(&tmp);
	return (le_struct->buff);
}

/*
**	Realloc the buffer if the command line is over than LE_BUFF_SIZE
*/

int		le_buff_history(struct s_le *le_struct)
{
	if (!le_struct->history_activ)
		while (le_struct->history->prev)
			le_struct->history = le_struct->history->prev;
	if (le_struct->term == LE_ARROW_UP && (!le_struct->nb_char || le_struct->history_activ))
	{
		ft_bzero(le_struct->buff, le_struct->nb_char);
		ft_strcpy(le_struct->buff, le_struct->history->content);
		le_struct->nb_char = ft_strlen(le_struct->history->content);
		if (le_clear(le_struct))
			return (LE_FAILURE);
		le_struct->cursor_x = le_struct->nb_char + le_struct->prompt_size;
		if (le_struct->history->next)
			le_struct->history = le_struct->history->next;
		le_struct->history_activ = 1;
	}
	if (le_struct->term == LE_ARROW_DOWN && (!le_struct->nb_char || le_struct->history_activ))
	{
		if (le_struct->history->prev)
			le_struct->history = le_struct->history->prev;
		ft_bzero(le_struct->buff, le_struct->nb_char);
		ft_strcpy(le_struct->buff, le_struct->history->content);
		le_struct->nb_char = ft_strlen(le_struct->history->content);
		if (le_clear(le_struct))
			return (LE_FAILURE);
		le_struct->cursor_x = le_struct->nb_char + le_struct->prompt_size;
		le_struct->history_activ = 1;
	}
	return (LE_SUCCESS);
}
