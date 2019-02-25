/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 16:48:36 by mrandou           #+#    #+#             */
/*   Updated: 2019/02/25 16:49:24 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_exit(struct s_le *le_struct, int ret)
{
	if (ret == LE_ENDL || ret == LE_EXIT)
	{
		le_free(le_struct);
		if (le_struct->term == LE_EOF)		//DELETE THIS. Just for test
			exit(0);						//DELETE THIS. Implement after the LE
		if (ret == LE_EXIT)
			ft_strclr(le_struct->buff);
		if (le_struct->prompt_type == DQUOTE || le_struct->prompt_type == SQUOTE)
		{
			if (le_buff_add(le_struct, 0, '\n'))
				return (LE_FAILURE);
			le_struct->nb_char++;
		}
		return (LE_EXIT);
	}
	else if (ret == LE_FAILURE)
	{
		le_free(le_struct);
		return (LE_FAILURE);
	}
	return (LE_SUCCESS);
}

/*
**	Exit and set the old shell attribute
*/

void	le_free(struct s_le *le_struct)
{
	if (le_struct->history_activ != -1)
		hy_dlst_free(le_struct->history);
	ft_strclr(le_struct->tmp);
	if (le_struct->clipboard)
		ft_strdel(&le_struct->clipboard);
	if (!le_struct->prompt_type)
		if (le_struct->git)
			ft_strdel(&le_struct->git);
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
