/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 23:05:19 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/17 17:15:56 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

static pid_t		getter_pid(pid_t val)
{
	static int		pid = 0;

	if (val != -1)
		pid = val;
	return (pid);
}

static void			sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		kill(sig, getter_pid(-1));
		ft_putstr_fd("21sh: Interrupt program. Signal received: ", 2);
		ft_putnbr_fd(sig, 2);
		ft_putendl_fd("", 2);
	}
}

int					sh_exec_binary(t_sh *shell)
{
	pid_t	pid;
	int		status;
	int		ret;

	ret = 0;
	status = 0;
	if (shell->fork == 0)
		ret = execve(shell->path, shell->cmd, shell->env);
	else
	{
		if ((pid = fork()) < 0)
			exit(1);
		if (pid == 0)
			ret = execve(shell->path, shell->cmd, shell->env);
		else
		{
			getter_pid(pid);
			signal(SIGINT, sig_handler);
			waitpid(pid, &status, 0);
			if (status > 0)
				ret = FAILURE;
		}
	}
	ft_strdel(&(shell->path));
	return (ret);
}
