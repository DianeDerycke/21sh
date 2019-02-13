/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:11:10 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/13 12:48:01 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

static int     exec_pipe_cmd(t_ast *ast)
{	
    t_sh    *shell;

	if (!ast)
		return (FAILURE);
	if (find_next_redir(ast))
		exec_redirection(ast);
    if (!(shell = sh_get_shell(ast)))
        return (FAILURE);
	if (just_exec(shell) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static void		end_recurse_pipe(t_ast *ast, int oldfd[], int newfd[])
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		close(newfd[INPUT_END]);
		dup2(newfd[OUTPUT_END], STDIN_FILENO);
		close(newfd[OUTPUT_END]);
		close(oldfd[OUTPUT_END]);
		close(oldfd[INPUT_END]);
		exec_pipe_cmd(ast);
	}
}

static void		recurse_pipe(t_ast *ast, int oldfd[])
{
	int		newfd[2];
	pid_t	child_pid;


	if (pipe(newfd) == -1)
		exit (2);
	child_pid = fork();
	if (child_pid == 0)
	{
		close(oldfd[INPUT_END]);
		dup2(oldfd[OUTPUT_END], STDIN_FILENO);
		close(oldfd[OUTPUT_END]);
		close(newfd[OUTPUT_END]);
		dup2(newfd[INPUT_END], STDOUT_FILENO);
		close(newfd[INPUT_END]);
		exec_pipe_cmd(ast->right);
	}
	if (ast->left && ast->left->token == PIPE)
	{
		close(oldfd[INPUT_END]);
		close(oldfd[OUTPUT_END]);
		recurse_pipe(ast->left, newfd);
	}
	else if (ast->left)
	{
		end_recurse_pipe(ast->left, oldfd, newfd);
		close(oldfd[INPUT_END]);
		close(oldfd[OUTPUT_END]);
	}
}

static void		end_pipe(t_ast *ast, int *fd)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == 0)
	{
		close(fd[INPUT_END]);
		dup2(fd[OUTPUT_END], STDIN_FILENO);
		close(fd[INPUT_END]);
		exec_pipe_cmd(ast);		
	}
}

void		do_pipe(t_ast *ast)
{
	pid_t	child_pid;
	int		fd[2];
	int		pipe_ret;
	int		status;
	
	pipe_ret = pipe(fd);
	if (pipe_ret == -1)
		exit (1);
	child_pid = fork();
	if (child_pid == -1)
		exit(1);
	if (child_pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		exec_pipe_cmd(ast->right);
	}
	if (ast->left && ast->left->token == PIPE)
		recurse_pipe(ast->left, fd);
	else if (ast->left)
		end_pipe(ast->left, fd);
	wait(NULL);
	close(fd[OUTPUT_END]);
	close(fd[INPUT_END]);
	waitpid(-1, &status, 0);
}