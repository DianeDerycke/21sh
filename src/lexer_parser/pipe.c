/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:11:10 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/06 18:59:34 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

static int     just_exec(t_sh *shell)
{
    char    *path;

    path = NULL;
    if ((path = ms_get_valid_cmd(shell->cmd[0], shell->env))
            && access(path, X_OK) == SUCCESS)
        execve(path, shell->cmd, shell->env);
    else if (!path)
        return (FAILURE);
    else 
        ms_perm_denied(shell->cmd[0]);
    ft_strdel(&path);
    return (SUCCESS);
}

static int     exec_pipe_cmd(t_ast *ast)
{	
    t_sh    *shell;

    if (!(shell = sh_get_shell(ast)))
        return (FAILURE);
    apply_expansions(shell);
    if ((exec_builtin(shell)) == FAILURE)
		if (just_exec(shell) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}

void    do_pipe(t_ast *ast)
{
    int		fd[2];
	int		ret;
	pid_t	pid;
	pid_t 	pid2;

	ret = pipe(fd);
	if (ret == -1)
		exit (2);
	if (ret == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			dup2(fd[1], 1);
			exec_pipe_cmd(ast->right);
			close(fd[1]);
		}
	}
		pid2 = fork();
		if (pid2 == -1)
			exit (2);
		if (pid2 == 0)
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			exec_pipe_cmd(ast->left);
		}
		else
		{
			close(fd[0]);
			close(fd[1]);
			wait(NULL);
		}
	wait(NULL);
	close(fd[0]);
	close(fd[1]);
}