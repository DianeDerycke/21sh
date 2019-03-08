/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:11:10 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/08 12:40:22 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

static int		handle_right_command(t_sh *shell, t_ast *ast, int *oldfd, int *newfd)
{
	if (oldfd)
		close_dup(oldfd, STDIN_FILENO);
	close_dup(newfd, STDOUT_FILENO);
	return (exec_pipe_cmd(shell, ast));
}

static int		end_recurse_pipe(t_sh *shell, t_ast *ast, int *oldfd, int *newfd)
{
	close_dup(newfd, STDIN_FILENO);
	close_pipe(oldfd);
	return (exec_pipe_cmd(shell, ast))
}

static int				recurse_pipe(t_sh *shell, t_ast *ast, int *oldfd, int *fd)
{
	int		newfd[2];
	pid_t	child_pid;
	int		status;
	int		ret;

	status = 0;
	ret = 0;
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
		if (ast->left && ast->left->token == PIPE)
			ret = recurse_pipe(shell, ast->left, newfd, NULL);
		else if (ast->left && ast->token == PIPE)
			ret = recurse_pipe(shell, ast->left, oldfd, newfd);
		sh_push_pidnew(child_pid, &(shell->l_pid));
		get_pid_list(shell->l_pid);
		signal(SIGINT, signal_handler);
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