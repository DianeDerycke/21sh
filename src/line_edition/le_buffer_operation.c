/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_buffer_operation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 17:47:26 by mrandou           #+#    #+#             */
/*   Updated: 2019/03/16 15:24:42 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_buff_append(struct s_le *le_struct, char c)
{
	if (c != LE_ENDL)
		if (le_buff_add(le_struct, le_struct->cursor_buff, c))
			return (LE_FAILURE);
	le_struct->cursor_x += 1;
	le_struct->nb_char += 1;
	le_struct->cursor_buff += 1;
	if (le_struct->cursor_buff != le_struct->nb_char
	|| le_struct->copy_on != LE_START)
	{
		le_struct->copy_on = LE_START;
		le_struct->copy_off = LE_START;
		if (le_window_clear_restore(le_struct))
			return (LE_FAILURE);
		if (le_struct->cursor_x == le_struct->w_col * le_struct->cursor_y)
			if (le_termcap_print(TC_GO_DOWN, 1))
				return (LE_FAILURE);
	}
	else
		le_buff_print(le_struct, le_struct->cursor_buff - 1);
	if (le_struct->history_activ != -1)
		le_struct->history_activ = 0;
	le_struct->copy_off = LE_START;
	return (LE_SUCCESS);
}

/*
**	Append the new read char to the buffer at cursor position
**	Clear at cursor position and print
*/

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
	le_struct->nb_char--;
	return (LE_SUCCESS);
}

/*
**	Delete a char at i position
*/

int		le_buff_add(struct s_le *le_struct, int i, char c)
{
	char	*tmp;
	int		len;

	if (!c)
		return (LE_FAILURE);
	if (i == le_struct->nb_char)
	{
		le_struct->buff[i] = c;
		return (LE_SUCCESS);
	}
	if (!(len = ft_strlen(le_struct->buff + i)))
		return (LE_SUCCESS);
	if (!(tmp = ft_strnew(len + 1)))
		return (LE_FAILURE);
	tmp[0] = c;
	ft_strcpy(tmp + 1, le_struct->buff + i);
	le_struct->buff[i] = '\0';
	le_struct->buff = ft_strcat(le_struct->buff, tmp);
	ft_strdel(&tmp);
	return (LE_SUCCESS);
}

/*
**	Add the c char at i position on the buffer and shift all chars after i
*/

int		le_buff_check_space(struct s_le *le_struct, int len)
{
	if (le_struct->nb_char != LE_START\
	&& le_struct->nb_char + len >= le_struct->buffer_size - 1)
		return (LE_REALLOC);
	return (0);
}

/*
**	Check if there is enough space on the buffer and the shell window
**	for more nb chars, if yes return 0
*/

int		le_buff_realloc(struct s_le *le_struct, int nb)
{
	char	*tmp;

	le_struct->buffer_size += LE_BUFF_SIZE + nb + 1;
	if (!(tmp = ft_strdup(le_struct->buff)))
		return (LE_FAILURE);
	ft_strdel(&le_struct->buff);
	if (!(le_struct->buff = (char *)malloc(sizeof(char)
	* (le_struct->buffer_size))))
	{
		ft_strdel(&tmp);
		return (LE_FAILURE);
	}
	ft_bzero(le_struct->buff, le_struct->buffer_size);
	if (!(le_struct->buff = ft_strcpy(le_struct->buff, tmp)))
	{
		ft_strdel(&tmp);
		return (LE_FAILURE);
	}
	ft_strdel(&tmp);
	return (LE_SUCCESS);
}

/*
**	Realloc the buffer if the command line is over than LE_BUFF_SIZE + nb
*/
