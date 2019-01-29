/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_cursor_tool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 15:54:51 by mrandou           #+#    #+#             */
/*   Updated: 2019/01/29 19:35:41 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_cursor_endl(struct s_le *le_struct)
{
	int nb_empty_char;

	nb_empty_char = (le_struct->cursor_x - 1) % le_struct->w_col;
	// nb_empty_char = le_struct->w_col - nb_empty_char;
	le_termcap_print(TC_GO_UP, 1);
	le_termcap_print(TC_GO_RIGHT, nb_empty_char - 1);
	le_struct->cursor_x -= 1;
	le_struct->cursor_y -= 1;
	return (LE_SUCCESS);
}

void	le_cursor_calcul_empty_char(struct s_le *le_struct, int max)
{
	int i;
	int endl;

	i = 0;
	le_struct->nb_empty_char = 0;
	while (le_struct->buff[i] && i < max)
	{
		if (le_struct->buff[i] == '\n')
		{
			endl = (i + le_struct->prompt_size - 1 + le_struct->nb_empty_char);
			endl = (endl % le_struct->w_col) + 1;
			le_struct->nb_empty_char += le_struct->w_col - endl;
		}
		i++;
	}
}
