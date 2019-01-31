/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 17:16:08 by mrandou           #+#    #+#             */
/*   Updated: 2019/01/31 10:39:00 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"


int		le_read_and_exec(struct s_le *le_struct)
{
	int	ret;

	if (le_init_struct(le_struct))
		return (LE_FAILURE);
	if (le_termcap_window_size(&le_struct->w_col, &le_struct->w_line))
		return (LE_FAILURE);
	while (21)
	{
		if (le_window_check(le_struct))
			return (LE_FAILURE);
		if ((ret = le_exit(le_struct, le_init(le_struct))) == LE_EXIT)
			return (LE_SUCCESS);
		else if (ret == LE_FAILURE)
			return (LE_FAILURE);
		if (read(STDIN_FILENO, le_struct->tmp, 1) == -1)
			return (LE_FAILURE);
		if ((le_struct->term = le_termcap_check(le_struct->tmp)) != LE_FAILURE\
		 && le_struct->term)
		 {
			if (le_termcap_exec(le_struct))
				return (LE_FAILURE);
		 }
		else if (!le_struct->term && ft_isprint(le_struct->tmp[0]))
		{
			if (le_buff_append(le_struct, le_struct->tmp[0]))
				return (LE_FAILURE);
		}
	}
	return (LE_FAILURE);
}

/*
**	Initialize the shell, and read char by char the standard input
**	Check if it's  a termcaps, if it's true, then launch the termacap function
**	Else add the char to the buffer
*/

char	*line_edition(int prompt)
{
	struct termios	backup;
	struct s_le		le_struct;

	le_struct.prompt_type = prompt;
	if (le_set_attribute(&backup))
		return (NULL);
	if (le_read_and_exec(&le_struct))
	{
		if (tcsetattr(STDIN_FILENO, 0, &backup))
			return (NULL);
		if (le_struct.buff)
			ft_strdel(&le_struct.buff);
		return (NULL);
	}
	if (tcsetattr(STDIN_FILENO, 0, &backup))
		return (NULL);
	if (!(le_struct.nb_char))
	{
		ft_strdel(&le_struct.buff);
		return (NULL);
	}
	return (le_struct.buff);
}

/*
**	le_ = line_edition
**	It's this function that will have to be called for line edition
**	Set the attribute for the shell and launch the read/execute function
*/
