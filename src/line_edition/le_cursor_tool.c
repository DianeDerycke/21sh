/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_cursor_tool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 15:54:51 by mrandou           #+#    #+#             */
/*   Updated: 2019/02/16 13:53:37 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_cursor_endl(struct s_le *le_struct)
{
	int endl;

	le_struct->cursor_buff = le_struct->cursor_x - le_struct->prompt_size;
	endl = le_calcul_empty_char(le_struct, le_struct->cursor_buff);
	le_struct->cursor_x += le_struct->nb_empty_char;
	if (le_clear_restore(le_struct))
		return (LE_FAILURE);
	le_struct->cursor_x -= le_struct->nb_empty_char;
	if (endl > 0)
		le_ansi_print(endl, LE_UP);
	return (LE_SUCCESS);
}

int		le_calcul_empty_char(struct s_le *le_struct, int max)
{
	int i;
	int endl;
	int count;

	i = 0;
	count = 0;
	le_struct->nb_empty_char = 0;
	while (le_struct->buff[i] && i < max)
	{
		if (le_struct->buff[i] == '\n')
		{
			count++;
			endl = (i + le_struct->prompt_size - 1 + le_struct->nb_empty_char);
			endl = (endl % le_struct->w_col) + 1;
			le_struct->nb_empty_char += le_struct->w_col - endl;
		}
		i++;
	}
	return (count);
}
