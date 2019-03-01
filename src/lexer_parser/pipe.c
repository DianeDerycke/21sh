/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:11:10 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/01 11:32:45 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

static int     exec_pipe_cmd(t_sh *shell, t_ast *ast)
{	
	if (!ast)
		return (FAILURE);
	if (find_next_redir(ast))
		return (exec_redirection(ast, shell));
	if (just_exec(ast, shell) == FAILURE)
		exit(1);
	return (SUCCESS);
}

void	double_close(int *fd)
{
	close(fd[INPUT_END]);
	close(fd[OUTPUT_END]);
}

void	handle_pipe(int *oldfd, int *newfd)
{
	close(oldfd[INPUT_END]);
	dup2(oldfd[OUTPUT_END], STDIN_FILENO);
	close(oldfd[OUTPUT_END]);
	close(newfd[OUTPUT_END]);
	dup2(newfd[INPUT_END], STDOUT_FILENO);
	close(newfd[INPUT_END]);
}

static void		end_recurse_pipe(t_sh *shell, t_ast *ast, int oldfd[], int newfd[])
{
	pid_t	child_pid;
	int		status;
	
	status = 0;
	child_pid = fork();
	if (child_pid == 0)
	{
		close(newfd[INPUT_END]);
		dup2(newfd[OUTPUT_END], STDIN_FILENO);
		close(newfd[OUTPUT_END]);
		double_close(oldfd);
		exec_pipe_cmd(shell, ast);
	}
	else
	{
		double_close(oldfd);
		double_close(newfd);
		waitpid(child_pid, &status, 0);
	}	
}

static void		recurse_pipe(t_sh *shell, t_ast *ast, int oldfd[])
{
	int		newfd[2];
	pid_t	child_pid;
	int		status;

	status = 0;
	if (!ast || (ast && ast->token != PIPE))
		return ;
	if (pipe(newfd) == -1)
		exit (1);
	child_pid = fork();
	if (child_pid == 0)
	{	
		handle_pipe(oldfd, newfd);
		exec_pipe_cmd(shell, ast->right);
	}
	else
	{
		double_close(oldfd);
		waitpid(child_pid, &status, 0);
	}
		if (ast->left && ast->left->token == PIPE)
			recurse_pipe(shell, ast->left, newfd);
		else if (ast->left)
			end_recurse_pipe(shell, ast->left, oldfd, newfd);
}

static void		end_pipe(t_sh *shell, t_ast *ast, int *fd)
{
	pid_t	child_pid;
	int		status;

	status = 0;
	if (!ast || (ast && ast->token == PIPE))
		return ;
	child_pid = fork();
	if (child_pid == 0)
	{
		close(fd[INPUT_END]);
		dup2(fd[OUTPUT_END], STDIN_FILENO);
		close(fd[OUTPUT_END]);
		exec_pipe_cmd(shell, ast);		
	}
	else
	{
		double_close(fd);
		waitpid(child_pid, &status, 0);
	}
}

void		do_pipe(t_ast *ast, t_sh *shell)
{
	pid_t	child_pid;
	int		fd[2];
	int		status;
	
	status = 0;
	if (pipe(fd) == -1)
		exit (1);
	child_pid = fork();
	if (child_pid == 0)
	{
		close(fd[OUTPUT_END]);
		dup2(fd[INPUT_END], STDIN_FILENO);
		close(fd[INPUT_END]);
		exec_pipe_cmd(shell, ast->right);
	}
	else 
	{
		recurse_pipe(shell, ast->left, fd);
		end_pipe(shell, ast->left, fd);
		get_pid(child_pid);
		signal(SIGINT, signal_handler);
		double_close(fd);
		waitpid(child_pid, &status, 0);
	}
}