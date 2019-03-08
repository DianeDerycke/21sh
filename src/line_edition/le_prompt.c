/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:44:04 by mrandou           #+#    #+#             */
/*   Updated: 2019/03/08 12:29:55 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_prompt_init(struct s_le *le_struct, char **env)
{
	if (le_struct->prompt_type != DQUOTE && le_struct->prompt_type != SQUOTE
	&& le_struct->prompt_type != IS_PIPE)
	{
		if (le_prompt_pwd(le_struct, env))
		{
			if (!(le_struct->prompt = ft_strdup(LE_PROMPT)))
				return (LE_FAILURE);
			ft_putstr(le_struct->prompt);
			le_struct->prompt_size = LE_PROMPT_DEF_SIZE;
			le_struct->prompt_type = LE_PROMPT_SIMPLE;
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
		{
			ft_strdel(&pwd);
			return (LE_FAILURE);
		}
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
		return (LE_FAILURE);
	else if (env[pos])
		home = ms_get_var_value(env[pos]);
	if (home)
	{
		len = ft_strlen(home);
		if (!ft_strncmp(home, pwd, len))
		{
			if (!(le_struct->prompt = ft_strjoin("~", pwd + len)))
				return (le_free_return(home, NULL, NULL, LE_FAILURE));
			le_struct->prompt_size += ft_strlen(le_struct->prompt) + 4;
			return (le_free_return(home, pwd, NULL, LE_SUCCESS));
		}
		ft_strdel(&home);
		return (LE_FAILURE);
	}
	return (LE_FAILURE);
}

/*
**	Get the "HOME" value for know if the current path are in the home of the
**	user, if it's right, replace the home value by '~'
*/

int		le_prompt_quote(struct s_le *le_struct)
{
	if (le_struct->prompt_type == DQUOTE)
		if (!(le_struct->prompt = ft_strdup(LE_PROMPT_DQUOTE)))
			return (LE_FAILURE);
	if (le_struct->prompt_type == SQUOTE)
		if (!(le_struct->prompt = ft_strdup(LE_PROMPT_SQUOTE)))
			return (LE_FAILURE);
	le_struct->prompt_size = LE_PROMPT_QTE_SIZE;	
	if (le_struct->prompt_type == IS_PIPE)
	{
		if (!(le_struct->prompt = ft_strdup(LE_PROMPT_PIPE)))
			return (LE_FAILURE);
		le_struct->prompt_size = LE_PROMPT_QTE_SIZE - 1;
	}
	le_prompt_print(le_struct);
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
