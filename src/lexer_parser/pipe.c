/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:11:10 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/04 16:38:36 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

static int		handle_right_command(int *oldfd, int *newfd, t_sh *shell, t_ast *ast)
{
	if (oldfd)
		close_dup(oldfd, STDIN_FILENO);
	close_dup(newfd, STDOUT_FILENO);
	return (exec_pipe_cmd(shell, ast));
}

static int		end_recurse_pipe(t_sh *shell, t_ast *ast, int *oldfd, int *newfd)
{
	pid_t	child_pid;
	int		status;
	
	status = 0;
	child_pid = fork();
	if (child_pid == 0)
	{
		close_dup(newfd, STDIN_FILENO);
		close_pipe(oldfd);
		return (exec_pipe_cmd(shell, ast));
	}
	else
	{
		close_pipe(oldfd);
		close_pipe(newfd);
		sh_push_pidnew(child_pid, &(shell->l_pid));
		get_pid_list(shell->l_pid);
		signal(SIGINT, signal_handler);
		waitpid(child_pid, &status, 0);
	}
	return (status);
}

int				recurse_pipe(t_sh *shell, t_ast *ast, int *oldfd)
{
	int		newfd[2];
	pid_t	child_pid;
	int		status;
	int		ret;

	ret = 0;
	if ((pipe(newfd) == -1) || ((child_pid = fork()) < 0))
		return (ERROR);
	if (child_pid == 0)
		ret = handle_right_command(oldfd, newfd, shell, ast->right);
	else
	{
		close_pipe(oldfd);
		if (ast->left && ast->left->token == PIPE)
			ret = recurse_pipe(shell, ast->left, newfd);
		else if (ast->left)
			ret = end_recurse_pipe(shell, ast->left, oldfd, newfd);
		sh_push_pidnew(child_pid, &(shell->l_pid));
		get_pid_list(shell->l_pid);
		signal(SIGINT, signal_handler);
		waitpid(child_pid, &status, 0);
	}
	return (ret);
}