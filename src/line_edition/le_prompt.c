/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:44:04 by mrandou           #+#    #+#             */
/*   Updated: 2019/03/17 14:15:38 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int		le_prompt_init(struct s_le *le_struct, char **env)
{
	if (le_prompt_get_color(le_struct, env))
		ft_strcpy(le_struct->prompt_color, LE_PROMPT_DFLT_CLR);
	if (le_struct->prompt_type != DQUOTE && le_struct->prompt_type != SQUOTE
	&& le_struct->prompt_type != IS_PIPE && le_struct->prompt_type != HEREDOC)
	{
		if (le_prompt_pwd(le_struct, env))
		{
			ft_strcpy(le_struct->prompt, LE_PROMPT_DFLT);
			le_struct->prompt_size = LE_PROMPT_DEF_SIZE;
			le_struct->prompt_type = LE_PROMPT_SIMPLE;
			le_prompt_print(le_struct);
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

	index = sh_find_variable("PWD", env, &pos);
	if (index == -1 || !(pwd = sh_get_var_value(env[pos])))
		return (LE_FAILURE);
	if (le_prompt_home(le_struct, env, pwd))
	{
		if (!le_prompt_shorten_path(le_struct, pwd))
			ft_strncpy(le_struct->prompt, pwd, LE_PROMPT_BUFF);
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

int		le_prompt_shorten_path(struct s_le *le_struct, char *path)
{
	int	i;
	int slash;

	i = 0;
	slash = 0;
	while (path[i])
	{
		if (path[i] == '/')
			slash++;
		if (slash == 4)
		{
			if (le_struct->prompt[0] == '~')
				ft_strncat(le_struct->prompt, "/../", LE_PROMPT_BUFF);
			else
				ft_strncat(le_struct->prompt, "../", LE_PROMPT_BUFF);
			while (path[i])
				if (path[i++] == '/')
					slash = i;
			ft_strncat(le_struct->prompt, path + slash, LE_PROMPT_BUFF);
			return (1);
		}
		i++;
	}
	return (0);
}

int		le_prompt_home(struct s_le *le_struct, char **env, char *pwd)
{
	char	*home;
	int		len;
	size_t	pos;

	home = NULL;
	if (!env || sh_find_variable("HOME", env, &pos) == -1)
		return (LE_FAILURE);
	else if (env[pos])
		home = sh_get_var_value(env[pos]);
	if (home)
	{
		len = ft_strlen(home);
		if (!ft_strncmp(home, pwd, len))
		{
			ft_strcpy(le_struct->prompt, "~");
			if (!le_prompt_shorten_path(le_struct, pwd))
				ft_strlcat(le_struct->prompt, pwd + len, LE_PROMPT_BUFF);
			le_struct->prompt_size += ft_strlen(le_struct->prompt) + 4;
			return ((int)sh_strmdel_return(home, pwd, NULL, LE_SUCCESS));
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
	if (le_struct->prompt_color[0]
	&& !ft_strcmp(le_struct->prompt_color, "ER"))
	{
		ft_strcpy(le_struct->prompt, "> ");
		le_struct->prompt_size = 2;
		le_prompt_print(le_struct);
		return (LE_SUCCESS);
	}
	if (le_struct->prompt_type == DQUOTE)
		ft_strcpy(le_struct->prompt, LE_PROMPT_DQUOTE);
	else if (le_struct->prompt_type == SQUOTE)
		ft_strcpy(le_struct->prompt, LE_PROMPT_SQUOTE);
	le_struct->prompt_size = LE_PROMPT_QTE_SIZE;
	if (le_struct->prompt_type == IS_PIPE)
	{
		ft_strcpy(le_struct->prompt, LE_PROMPT_PIPE);
		le_struct->prompt_size = LE_PROMPT_QTE_SIZE - 1;
	}
	else if (le_struct->prompt_type == HEREDOC)
	{
		ft_strcpy(le_struct->prompt, LE_PROMPT_HEREDOC);
		le_struct->prompt_size = LE_PROMPT_HER_SIZE;
	}
	le_prompt_print(le_struct);
	return (LE_SUCCESS);
}

/*
**	Initialise the prompt with the quote prompt
*/
