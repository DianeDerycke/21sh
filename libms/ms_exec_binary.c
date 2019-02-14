/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 14:26:30 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/14 16:57:08 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

int		ms_exec_binary(char *utility, char **split_cmd, char **env, char **tmp)
{
	char	*path;
	pid_t	pid;
	int		status;
	int		ret;

	path = NULL;
	ret = 0;
	if ((path = ms_get_valid_cmd(utility, env))
		&& access(path, X_OK) == SUCCESS)
	{
		pid = fork ();
		if (pid == 0)
			execve(path, split_cmd, tmp);
		else
		{
			// if (signal(SIGINT, handle_sigint))
			// 	kill(pid, SIGINT);
			waitpid(-1, &status, 0);
		}
	}
	else if (!path)
		ret = ERROR;
	else
		ret = ms_perm_denied(split_cmd[0]);
	ft_strdel(&path);
	return (ret);
}