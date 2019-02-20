/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_cursor_tool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 15:54:51 by mrandou           #+#    #+#             */
/*   Updated: 2019/02/20 12:23:38 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_cursor_endl(struct s_le *le_struct)
{
	int endl;

	le_struct->cursor_buff = le_struct->cursor_x - le_struct->prompt_size;
	le_struct->nb_empty_char = le_calcul_empty_char(le_struct, le_struct->cursor_buff);
	endl = le_count_occ(le_struct->buff, LE_ENDL);
 	le_struct->cursor_x += le_struct->nb_empty_char;
	// le_struct->nb_char += le_struct->nb_empty_char;
	if (le_clear_restore(le_struct))
		return (LE_FAILURE);
	le_struct->cursor_x -= le_struct->nb_empty_char;
	// le_struct->nb_char -= le_struct->nb_empty_char;
	if (endl)
		le_ansi_print(endl, LE_UP);
	return (LE_SUCCESS);
}

int		le_calcul_empty_char(struct s_le *le_struct, int max)
{
	int i;
	int endl;
	int nb_empty_char;

	i = 0;
	endl = 0;
	nb_empty_char = 0;
	while (le_struct->buff[i] && i < max)
	{
		if (le_struct->buff[i] == '\n')
		{
			endl = (i + le_struct->prompt_size - 1 + nb_empty_char);
			endl = (endl % le_struct->w_col) + 1;
			nb_empty_char += le_struct->w_col - endl;
		}
		i++;
	}
	return (nb_empty_char);
}

int		le_count_occ(char *str, char oc)
{
	int count;

	count = 0;
	while (*str)
		if (*(str++) == oc)
			count++;
	return (count);
}
