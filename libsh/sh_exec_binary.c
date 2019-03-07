/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exec_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 23:05:19 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/07 03:22:52 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

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

int		sh_exec_binary(t_sh *shell)
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
        pid = fork();
        if (pid < 0)
            exit(1);
        if (pid == 0)
            ret = execve(shell->path, shell->cmd, shell->env);
        else
        {
            getter_pid(pid);
            signal(SIGINT, sig_handler);
            waitpid(pid, &status, 0);
        }
    }
	ft_strdel(&(shell->path));
	return (ret);
}