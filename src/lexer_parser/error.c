/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:07:12 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/14 16:16:00 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

ssize_t     error_arg(void)
{
    ft_putendl("Number args or args unvalid");
    return (FAILURE);
}

void		error_option(char c)
{
	ft_putstr_fd("env: illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("\nusage: env [-iv] [-P utilpath] [-S string] [-u name]", 2);
	ft_putendl_fd("           [name=value ...] [utility [argument ...]]", 2);
}

ssize_t		too_many_args(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": Too many arguments.", 2);
	return (FAILURE);
}

ssize_t		unvalid_setenv_cmd(void)
{
	ft_putstr_fd("setenv: ", 2);
	ft_putendl_fd("Variable name must contain alphanumeric characters.", 2);
	return (FAILURE);
}

ssize_t		error_chdir(int error, char *path, char *cmd)
{
	struct stat		f_stat;

	if (error == -1 && ms_file_exist(path) == SUCCESS)
	{
		if (lstat(path, &f_stat) == 0 && !(f_stat.st_mode & S_IXUSR))
			return (ms_error_perm_denied(cmd, path));
	}
	else
		return (ms_no_such_file_or_dir(cmd, path));
	return (FAILURE);
}

int			ambiguous_redirect(char *arg)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": ambiguous redirect", 2);
	return (ERROR);
}