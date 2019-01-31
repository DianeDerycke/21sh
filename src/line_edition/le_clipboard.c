/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_clipboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 13:09:48 by mrandou           #+#    #+#             */
/*   Updated: 2019/01/31 19:40:50 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_clipboard(struct s_le *le_struct)
{
	if (le_struct->term == LE_COPY)
		if (le_clipboard_copy(le_struct))
			return (LE_FAILURE);
	if (le_struct->term == LE_CUT)
	{
		if (le_clipboard_cut(le_struct))
			return (LE_FAILURE);
		le_struct->cursor_x -= ft_strlen(le_struct->clipboard);
		le_struct->nb_char -= ft_strlen(le_struct->clipboard);
		if (le_clear_restore(le_struct))
			return (LE_FAILURE);
	}
	if (le_struct->term == LE_PASTE)
	{
		if (le_clipboard_paste(le_struct))
			return (LE_FAILURE);
		le_struct->cursor_x += ft_strlen(le_struct->clipboard);
		le_struct->nb_char += ft_strlen(le_struct->clipboard);
		if (le_clear_restore(le_struct))
			return (LE_FAILURE);
	}
	return (LE_SUCCESS);
}

int		le_clipboard_copy(struct s_le *le_struct)
{
	int	tmp;

	if (!le_struct->copy_on)
		le_struct->copy_on = le_struct->cursor_buff;
	else if (!le_struct->copy_off)
	{
		le_struct->copy_off = le_struct->cursor_buff;
		if (le_struct->copy_off < le_struct->copy_on)
		{
			tmp = le_struct->copy_off;
			le_struct->copy_off = le_struct->copy_on;
			le_struct->copy_on = tmp;
		}
		if (!(tmp = le_struct->copy_off - le_struct->copy_on))
			tmp = 1;
		if (le_struct->clipboard)
			ft_strdel(&le_struct->clipboard);
		if (!(le_struct->clipboard = ft_strnew(tmp)))
			return (LE_FAILURE);
		le_struct->clipboard = ft_strncpy(le_struct->clipboard,\
		 &le_struct->buff[le_struct->copy_on], tmp);
	}
	return (LE_SUCCESS);
}

char	*ft_strpcat(char *dst, char *src, int pos)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!(tmp = ft_strdup(&dst[pos])))
		return (NULL);
	while (src[i])
		dst[pos++] = src[i++];
	i = 0;
	while (tmp[i])
		dst[pos++] = tmp[i++];
	dst[pos] = '\0';
	ft_strdel(&tmp);
	return (dst);
}

int		le_clipboard_paste(struct s_le *le_struct)
{
	int size;

	if (!(le_struct->clipboard))
		return (LE_SUCCESS);
	size = ft_strlen(le_struct->clipboard);
	if (!(le_buff_check_space(le_struct, size)))
		if (!(le_struct->buff = le_buff_realloc(le_struct, size)))
			return (LE_FAILURE);
	if (!(le_struct->buff = \
	ft_strpcat(le_struct->buff, le_struct->clipboard, le_struct->cursor_buff)))
		return (LE_FAILURE);
	return (LE_SUCCESS);
}

int		le_clipboard_cut(struct s_le *le_struct)
{
	int	i;
	int	size;

	if (!le_struct->copy_on)
		return (LE_SUCCESS);
	if (le_clipboard_copy(le_struct))
		return (LE_FAILURE);
	i = le_struct->copy_on;
	size = ft_strlen(&le_struct->buff[le_struct->copy_off]);
	while (le_struct->buff && i < size)
	{
		le_struct->buff[i] = le_struct->buff[le_struct->copy_off + i];
		i++;
	}
	le_struct->buff[i] = '\0';
	return (LE_SUCCESS);
}
