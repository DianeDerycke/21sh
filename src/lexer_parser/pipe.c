/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:11:10 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/01 16:29:35 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

static void		close_pipe(int *fd)
{
	if (!fd)
		return ;
	close(fd[INPUT_END]);
	close(fd[OUTPUT_END]);
}

static void		close_dup(int *fd, int std)
{
	if (!fd)
		return ;
	close(fd[std == STDIN_FILENO ? INPUT_END : OUTPUT_END]);
	dup2(fd[std == STDIN_FILENO ? OUTPUT_END : INPUT_END], std);
	close(fd[std == STDIN_FILENO ? OUTPUT_END : INPUT_END]);
}

static void		end_recurse_pipe(t_sh *shell, t_ast *ast, int *oldfd, int *newfd)
{
	pid_t	child_pid;
	int		status;
	
	status = 0;
	child_pid = fork();
	if (child_pid == 0)
	{
		close_dup(newfd, STDIN_FILENO);
		if (oldfd)
			close_pipe(oldfd);
		exec_pipe_cmd(shell, ast);
	}
	else
	{
		if (oldfd)
			close_pipe(oldfd);
		close_pipe(newfd);
		get_pid(child_pid);
		signal(SIGINT, signal_handler);
		waitpid(child_pid, &status, 0);
	}
}

void		recurse_pipe(t_sh *shell, t_ast *ast, int *oldfd)
{
	int		newfd[2];
	pid_t	child_pid;
	int		status;

	status = 0;
	if (pipe(newfd) == -1)
		exit (1);
	child_pid = fork();
	if (child_pid == 0)
	{
		if (oldfd)	
			close_dup(oldfd, STDIN_FILENO);
		close_dup(newfd, STDOUT_FILENO);
		exec_pipe_cmd(shell, ast->right);
	}
	else
	{
		if (oldfd)
			close_pipe(oldfd);
		get_pid(child_pid);
		signal(SIGINT, signal_handler);
		waitpid(child_pid, &status, 0);
		if (ast->left && ast->left->token == PIPE)
			recurse_pipe(shell, ast->left, newfd);
		else if (ast->left)
			end_recurse_pipe(shell, ast->left, oldfd, newfd);
	}
}