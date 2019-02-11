/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:44:04 by mrandou           #+#    #+#             */
/*   Updated: 2019/02/11 16:46:14 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_prompt_init(struct s_le *le_struct)
{
	char *pwd;

	pwd = NULL;
	le_struct->prompt = NULL;
	if (!le_struct->prompt_type)
	{
		if (!(pwd = getenv("PWD")))
		{
			if (!(le_struct->prompt = ft_strdup(LE_PROMPT)))
				return (LE_FAILURE);
			ft_putstr(le_struct->prompt);
			le_struct->prompt_size = LE_PROMPT_SIZE + 1;
		}
		else
		{
			if (!(le_struct->prompt = ft_strdup(pwd)))
				return (LE_FAILURE);
			le_prompt_print(le_struct);
			le_struct->prompt_size = ft_strlen(le_struct->prompt) + 4;
		}
	}
	else
	{
		if (!(le_struct->prompt = ft_strdup(LE_PROMPT_MIN)))
			return (LE_FAILURE);
		le_prompt_print(le_struct);		
		le_struct->prompt_size = 4;
	}
	return (LE_SUCCESS);
}

void	le_prompt_print(struct s_le *le_struct)
{
	if (!le_struct->prompt_type)
	{
		ft_putstr("\033[1m\033[32m");
		ft_putstr(le_struct->prompt);
		ft_putstr(" > ");
		ft_putstr("\033[0m");
	}
	else
		ft_putstr(le_struct->prompt);		
}
