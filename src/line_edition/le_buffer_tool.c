/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_buffer_tool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:33:43 by mrandou           #+#    #+#             */
/*   Updated: 2019/03/02 15:46:13 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

void	le_buff_print(struct s_le *le_struct, int pos)
{
	if (!le_struct->buff)
		return ;
	le_struct->cursor_buff = le_struct->cursor_x - le_struct->prompt_size;
	le_buff_truncate(le_struct, &le_struct->nb_char);
	le_buff_print_select(le_struct,\
	pos, le_struct->copy_on, le_struct->copy_off);
}

void	le_buff_print_select(struct s_le *le_struct, int pos, int on, int off)
{
	int tmp;

	tmp = 0;
	if (off == LE_START)
		off = le_struct->cursor_buff;
	if (off < on)
	{
		tmp = on;
		on = off;
		off = tmp;
	}
	while (le_struct->buff && le_struct->buff[pos])
	{
		if (on != LE_START && pos >= on && pos <= off)
		{
			ft_putstr(LE_SELECT_ON);
			ft_putchar(le_struct->buff[pos]);
			ft_putstr(LE_TERM_OFF);
		}
		else
			ft_putchar(le_struct->buff[pos]);
		pos++;
	}
}

/*
**	If the select mode is activate, print the buffer with invert colors
**	for the select area. Else print char by char
*/

void	le_buff_truncate(struct s_le *le_struct, int *len)
{
	if (*len > le_struct->max_size)
	{
		ft_strclr(&le_struct->buff[le_struct->max_size]);
		*len = le_struct->max_size;
		le_struct->cursor_x = le_struct->nb_char + le_struct->prompt_size;
	}
}

/*
**	Check if the shell window can receve all chars of the buffer, or delete
**	surplus
*/
