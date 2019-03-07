/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:11:10 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/07 13:59:16 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

static int		handle_right_command(t_sh *shell, t_ast *ast, int *oldfd, int *newfd)
{
	if (oldfd)
		close_dup(oldfd, STDIN_FILENO);
	close_dup(newfd, STDOUT_FILENO);
	if ((exec_pipe_cmd(shell, ast)) == FAILURE)
		return (ERROR);
	return (SUCCESS);
}

static int		end_recurse_pipe(t_sh *shell, t_ast *ast, int *oldfd, int *newfd)
{
	close_dup(newfd, STDIN_FILENO);
	close_pipe(oldfd);
	return(exec_pipe_cmd(shell, ast));
}

static int				recurse_pipe(t_sh *shell, t_ast *ast, int *oldfd, int *fd)
{
	int		newfd[2];
	pid_t	child_pid;
	int		status;

	status = 0;
	if (!fd)
		if (pipe(newfd) == ERROR)
			return (ERROR);
	child_pid = fork();
	if (child_pid < 0)
		return (ERROR);
	if (child_pid == 0)
	{
		if (fd)
			end_recurse_pipe(shell, ast, oldfd, fd);
		else
			handle_right_command(shell, ast->right, oldfd, newfd);
	}
	else
	{
		close_pipe(fd);
		close_pipe(oldfd);
		sh_push_pidnew(child_pid, &(shell->l_pid));
		get_pid_list(shell->l_pid);
		signal(SIGINT, signal_handler);
		if (ast->left && ast->left->token == PIPE)
			recurse_pipe(shell, ast->left, newfd, NULL);
		else if (ast->left && ast->token == PIPE)
			recurse_pipe(shell, ast->left, oldfd, newfd);
		waitpid(child_pid, &status, 0);
	}
	return (SUCCESS);
}

int 	do_pipe(t_sh *shell, t_ast *ast)
{
	int		ret;

	shell->fork = 0;
	ret = recurse_pipe(shell, ast, NULL, NULL);
	sh_freepidlist(&(shell->l_pid));
	shell->l_pid = NULL;
	return (ret);
}