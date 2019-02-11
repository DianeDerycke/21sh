/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:44:04 by mrandou           #+#    #+#             */
/*   Updated: 2019/02/11 18:16:59 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_prompt_init(struct s_le *le_struct)
{
	le_struct->prompt = NULL;
	if (!le_struct->prompt_type)
	{
		if (le_prompt_pwd(le_struct))
			if (le_prompt_simple(le_struct))
				return (LE_FAILURE);
	}
	else
		if (le_prompt_quote(le_struct))
			return (LE_FAILURE);
	return (LE_SUCCESS);
}

int		le_prompt_simple(struct s_le *le_struct)
{
	if (!(le_struct->prompt = ft_strdup(LE_PROMPT)))
		return (LE_FAILURE);
	ft_putstr(le_struct->prompt);
	le_struct->prompt_size = LE_PROMPT_SIZE + 1;
	le_struct->prompt_type = 1;
	return (LE_SUCCESS);
}

int		le_prompt_pwd(struct s_le *le_struct)
{
	char	*home;
	char	*pwd;
	int		len;

	home = getenv("HOME");
	if (!(pwd = getenv("PWD")))
		return (LE_FAILURE);
	if (home)
	{
		len = ft_strlen(home);
		if (!ft_strncmp(home, pwd, len))
			if (!(le_struct->prompt = ft_strjoin("~", pwd + len)))
				return (LE_FAILURE);
		le_struct->prompt_size = ft_strlen(le_struct->prompt) + 4;
	}
	else
	{
		if (!(le_struct->prompt = ft_strdup(pwd)))
			return (LE_FAILURE);
		le_struct->prompt_size = ft_strlen(le_struct->prompt) + 4;
	}	
	le_prompt_print(le_struct);
	return (LE_SUCCESS);
}

int		le_prompt_quote(struct s_le *le_struct)
{
	if (!(le_struct->prompt = ft_strdup(LE_PROMPT_MIN)))
		return (LE_FAILURE);
	le_prompt_print(le_struct);
	le_struct->prompt_size = 4;
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
