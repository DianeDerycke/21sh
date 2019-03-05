/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 14:26:30 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/05 16:08:48 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libms.h"

static pid_t		getter_pid(pid_t val)
{
	static int 		pid = 0;
	if (val != -1)
		pid = val;
	return (pid);
}

static void		sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		kill(sig, getter_pid(-1));
		ft_putstr_fd("21sh: Interrupt program. Signal received: ", 2);
		ft_putnbr_fd(sig, 2);
		ft_putendl_fd("", 2);
	}
}

int		ms_exec_binary(char *utility, char **split_cmd, char **env, char **tmp)
{
	char	*path;
	pid_t	pid;
	int		status;
	int		ret;

	ret = 0;
	status = 0;
	if ((path = ms_get_valid_cmd(utility, env))
		&& access(path, X_OK) == SUCCESS)
	{
		pid = fork();
		if (pid == 0)
			ret = execve(path, split_cmd, tmp);
		else
		{
			getter_pid(pid);
			signal(SIGINT, sig_handler);
			waitpid(-1, &status, 0);
		}
		if (status)
			ret = FAILURE;
	}
	else
		ret = ERROR;
	ft_strdel(&path);
	return (ret);
}