/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 16:48:36 by mrandou           #+#    #+#             */
/*   Updated: 2019/03/09 15:51:40 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_exit(struct s_le *le_struct)
{
	if (le_cursor_beggin(le_struct, le_struct->cursor_x))
		return (LE_FAILURE);
	le_struct->cursor_x = le_struct->nb_char + le_struct->prompt_size;
	if (le_cursor_restore(le_struct))
		return (LE_FAILURE);
	if (le_struct->tmp[0] != LE_ENDL)
		ft_strclr(le_struct->buff);
	if ((le_struct->term == LE_EOF || le_struct->term == LE_ETX)
	&& (le_struct->prompt_type == SQUOTE || le_struct->prompt_type == DQUOTE
	|| le_struct->prompt_type == HEREDOC || le_struct->prompt_type == IS_PIPE))
	{
		le_struct->buff = ft_strcpy(le_struct->buff, 
		le_struct->term == LE_EOF ? "\004" : "\003");
		le_struct->nb_char = 1;
	}
	else if (le_struct->term == LE_EOF)
	{
		le_struct->buff = ft_strcpy(le_struct->buff, "exit");
		le_buff_print(le_struct, 0);
		le_struct->nb_char = 4;
	}
	if (le_struct->prompt_type == DQUOTE || le_struct->prompt_type == SQUOTE)
		if (le_buff_add(le_struct, 0, '\n'))
			return (LE_FAILURE);
	ft_putchar(LE_ENDL);
	return (LE_SUCCESS);
}

void	le_free(struct s_le *le_struct)
{
	if (le_struct->history_activ != -1)
		hy_dlst_free(le_struct->history);
	ft_strclr(le_struct->tmp);
	if (le_struct->clipboard)
		ft_strdel(&le_struct->clipboard);
	if (le_struct->prompt)
			ft_strdel(&le_struct->prompt);
}

/*
**	Free the allocated memory for the line edition structure
*/

int		le_free_return(char *s1, char *s2, char *s3, int status)
{
	if (s1)
		ft_strdel(&s1);
	if (s2)
		ft_strdel(&s2);
	if (s3)
		ft_strdel(&s3);
	return (status);
}
