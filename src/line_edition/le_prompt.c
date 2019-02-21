/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:44:04 by mrandou           #+#    #+#             */
/*   Updated: 2019/02/21 19:35:34 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_prompt_init(struct s_le *le_struct, char **env)
{
	le_struct->prompt = NULL;
	if (!le_struct->prompt_type)
	{
		if (le_prompt_pwd(le_struct, env))
		{
			if (!(le_struct->prompt = ft_strdup(LE_PROMPT)))
				return (LE_FAILURE);
			ft_putstr(le_struct->prompt);
			le_struct->prompt_size = LE_PROMPT_SIZE + 1;
			le_struct->prompt_type = 1;
		}
	}
	else
	{
		if (le_prompt_quote(le_struct))
			return (LE_FAILURE);
	}
	return (LE_SUCCESS);
}

int		le_prompt_pwd(struct s_le *le_struct, char **env)
{
	char	*pwd;
	int		index;
	size_t	pos;

	index = ms_find_variable("PWD", env, &pos);
	if (index == -1 || !(pwd = ms_get_var_value(env[pos])))
		return (LE_FAILURE);
	if (le_prompt_home(le_struct, env, pwd))
	{
		if (!(le_struct->prompt = ft_strdup(pwd)))
			return (LE_FAILURE);
		le_struct->prompt_size = ft_strlen(le_struct->prompt) + 4;
	}
	le_prompt_print(le_struct);
	return (LE_SUCCESS);
}

int		le_prompt_home(struct s_le *le_struct, char **env, char *pwd)
{
	char	*home;
	int		len;
	size_t	pos;

	home = NULL;
	if (!env || ms_find_variable("HOME", env, &pos) == -1)
		home = NULL;
	else if (env[pos])
		home = ms_get_var_value(env[pos]);
	if (home)
	{
		len = ft_strlen(home);
		if (!ft_strncmp(home, pwd, len))
			if (!(le_struct->prompt = ft_strjoin("~", pwd + len)))
				return (LE_FAILURE);
		le_struct->prompt_size = ft_strlen(le_struct->prompt) + 4;
	}
	else
		return (LE_FAILURE);
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
		ft_putstr(LE_PROMPT_CLR);
		ft_putstr(le_struct->prompt);
		ft_putstr(" > ");
		ft_putstr(LE_TERM_OFF);
	}
	else
		ft_putstr(le_struct->prompt);
}
