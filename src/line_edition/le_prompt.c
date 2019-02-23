/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:44:04 by mrandou           #+#    #+#             */
/*   Updated: 2019/02/23 19:10:28 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_prompt_init(struct s_le *le_struct, char **env)
{
	le_struct->prompt = NULL;
	// if (le_struct->prompt_type != DQUOTE && le_struct->prompt_type != SQUOTE)
	if (!le_struct->prompt_type)
	{
		le_prompt_git(le_struct);
		if (le_prompt_pwd(le_struct, env))
		{
			if (!(le_struct->prompt = ft_strdup(LE_PROMPT)))
				return (LE_FAILURE);
			ft_putstr(le_struct->prompt);
			le_struct->prompt_size = LE_PROMPT_DEF_SIZE;
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

/*
**	Initialise the prompt, if the environement does not content the "PWD" value
**	initialise the prompt with a default prompt
**	If it's a multiple command, call le_prompt_quote for the initialise the
**	quote prompt
*/

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
		le_struct->prompt_size += ft_strlen(le_struct->prompt) + 4;
		ft_strdel(&pwd);
	}
	le_prompt_print(le_struct);
	return (LE_SUCCESS);
}

/*
**	Get the "PWD" value for print the current path in the prompt
**	Print the prompt
*/

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
		le_struct->prompt_size += ft_strlen(le_struct->prompt) + 4;
		ft_strdel(&home);
		ft_strdel(&pwd);
	}
	else
		return (LE_FAILURE);
	return (LE_SUCCESS);
}

/*
**	Get the "HOME" value for know if the current path are in the home of the
**	user, if it's right, replace the home value by '~'
*/

int		le_prompt_quote(struct s_le *le_struct)
{
	if (!(le_struct->prompt = ft_strdup(LE_PROMPT_QUOTE)))
		return (LE_FAILURE);
	le_prompt_print(le_struct);
	le_struct->prompt_size = LE_PROMPT_DEF_SIZE;
	return (LE_SUCCESS);
}

/*
**	Initialise the prompt with the quote prompt
*/

void	le_prompt_print(struct s_le *le_struct)
{
	if (le_struct->prompt_type == SUCCESS || le_struct->prompt_type == FAILURE)
	{
		ft_putstr(LE_PROMPT_CLR);
		ft_putstr(le_struct->prompt);
		le_prompt_git_print(le_struct);
		if (le_struct->prompt_type == SUCCESS)
			ft_putstr(LE_PROMPT_CLR" > ");
		else
			ft_putstr(LE_FAILURE_CLR" > ");
		ft_putstr(LE_TERM_OFF);
	}
	else
		ft_putstr(le_struct->prompt);
}

/*
**	Print the prompt with colors, Print the prompt with colors
**	if the last command was succesful print the '>' in green else with red
*/
