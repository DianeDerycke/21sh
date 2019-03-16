/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   le_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:44:04 by mrandou           #+#    #+#             */
/*   Updated: 2019/03/16 14:29:43 by DERYCKE          ###   ########.fr       */
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
			return ((int)le_free_return(home, pwd, NULL, LE_SUCCESS));
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
		ft_strcpy(le_struct->prompt, LE_PROMPT_DQUOTE);
	if (le_struct->prompt_type == SQUOTE)
		ft_strcpy(le_struct->prompt, LE_PROMPT_SQUOTE);
	le_struct->prompt_size = LE_PROMPT_QTE_SIZE;
	if (le_struct->prompt_type == IS_PIPE)
	{
		ft_strcpy(le_struct->prompt, LE_PROMPT_PIPE);
		le_struct->prompt_size = LE_PROMPT_QTE_SIZE - 1;
	}
	if (le_struct->prompt_type == HEREDOC)
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

void	le_prompt_print(struct s_le *le_struct)
{
	if (le_struct->prompt_type == SUCCESS || le_struct->prompt_type == FAILURE)
	{
		ft_putstr(LE_PROMPT_BOLD);
		ft_putstr(le_struct->prompt_color);
		ft_putstr(le_struct->prompt);
		if (!ft_strcmp(le_struct->prompt_color, RED))
			ft_putstr(GREEN);
		if (le_struct->prompt_type == SUCCESS)
			ft_putstr(" > ");
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

int		le_prompt_get_color(struct s_le *le_struct, char **env)
{
	int		fd;
	char	*path;
	char	*line;
	size_t	pos;

	path = NULL;
	line = NULL;
	if (!env || sh_find_variable("HOME", env, &pos) == -1)
		return (LE_FAILURE);
	if (!(path = sh_get_var_value(env[pos])))
		return (LE_FAILURE);
	if (!(path = ft_strjoin_free(path, LE_SHRC)))
		return (LE_FAILURE);
	if ((fd = open(path, O_RDONLY)) == -1)
		return (LE_FAILURE);
	ft_strdel(&path);
	if (get_next_line(fd, &line) == -1)
	{
		close(fd);
		return (LE_FAILURE);
	}
	close(fd);
	return (le_prompt_check_color(le_struct, line));
}

int		le_prompt_check_color(struct s_le *le_struct, char *line)
{
	ft_bzero(le_struct->prompt_color, 16);
	if (!ft_strcmp(ft_strchr(line, '=') + 1, "white"))
		ft_strcpy(le_struct->prompt_color, WHITE);
	if (!ft_strcmp(ft_strchr(line, '=') + 1, "red"))
		ft_strcpy(le_struct->prompt_color, RED);
	if (!ft_strcmp(ft_strchr(line, '=') + 1, "green"))
		ft_strcpy(le_struct->prompt_color, GREEN);
	if (!ft_strcmp(ft_strchr(line, '=') + 1, "yellow"))
		ft_strcpy(le_struct->prompt_color, YELLOW);
	if (!ft_strcmp(ft_strchr(line, '=') + 1, "blue"))
		ft_strcpy(le_struct->prompt_color, BLUE);
	if (!ft_strcmp(ft_strchr(line, '=') + 1, "magenta"))
		ft_strcpy(le_struct->prompt_color, MAGENTA);
	if (!ft_strcmp(ft_strchr(line, '=') + 1, "cyan"))
		ft_strcpy(le_struct->prompt_color, CYAN);
	ft_strdel(&line);
	if (le_struct->prompt_color[0])
		return (LE_SUCCESS);
	return (LE_FAILURE);
}
