/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_buffer_operation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 17:47:26 by mrandou           #+#    #+#             */
/*   Updated: 2019/02/21 17:30:11 by mrandou          ###   ########.fr       */
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
	if (le_struct->cursor_buff != le_struct->nb_char - 1)
	{
		if (le_window_clear_restore(le_struct))
			return (LE_FAILURE);
	}
	else
		le_buff_print(le_struct, le_struct->cursor_buff);
	if (le_struct->history_activ != -1)
		le_struct->history_activ = 0;
	le_struct->copy_on = LE_START;
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

char	*le_buff_realloc(struct s_le *le_struct, int nb)
{
	char	*tmp;

	if (le_struct->nb_char + nb < le_struct->buffer_size\
	|| le_struct->nb_char + nb > le_struct->max_size)
		return (le_struct->buff);
	le_struct->buffer_size += LE_BUFF_SIZE + nb;
	if (!(tmp = ft_strdup(le_struct->buff)))
		return (NULL);
	ft_strdel(&le_struct->buff);
	if (!(le_struct->buff = (char *)malloc(sizeof(char *)\
	* le_struct->buffer_size)))
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
**	Check if there is enough place on the buffer for more nb chars
**	Realloc the buffer if the command line is over than LE_BUFF_SIZE + nb
*/
