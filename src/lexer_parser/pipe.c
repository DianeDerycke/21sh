/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:11:10 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/27 18:38:21 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

pid_t	get_pid(pid_t val)
{
	static int 		pid;
	if (val != -1)
		pid = val;
	return (pid);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		kill(sig, get_pid(-1));
		ft_putstr_fd("21sh: Interrupt program. Signal received: ", 2);
		ft_putnbr_fd(sig, 2);
		ft_putendl_fd("", 2);
	}
}

static int     exec_pipe_cmd(t_sh *shell, t_ast *ast)
{	
	if (!ast)
		return (FAILURE);
	if (find_next_redir(ast))
		exec_redirection(ast, shell);
	shell->cmd = sh_rtree_to_array(ast);
	if (just_exec(ast, shell) == FAILURE)
		exit(1);
	return (SUCCESS);
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
		close(oldfd[OUTPUT_END]);
		close(oldfd[INPUT_END]);
		exec_pipe_cmd(shell, ast);
	}
	else
	{
		get_pid(child_pid);
		signal(SIGINT, signal_handler);
		waitpid(child_pid, &status, 0);
	}
	
}

static void		recurse_pipe(t_sh *shell, t_ast *ast, int oldfd[])
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
		close(oldfd[INPUT_END]);
		dup2(oldfd[OUTPUT_END], STDIN_FILENO);
		close(oldfd[OUTPUT_END]);
		close(newfd[OUTPUT_END]);
		dup2(newfd[INPUT_END], STDOUT_FILENO);
		close(newfd[INPUT_END]);
		exec_pipe_cmd(shell, ast->right);
	}
	if (ast->left && ast->left->token == PIPE)
	{
		close(oldfd[INPUT_END]);
		close(oldfd[OUTPUT_END]);
		recurse_pipe(shell, ast->left, newfd);
	}
	else if (ast->left)
	{
		end_recurse_pipe(shell, ast->left, oldfd, newfd);
		close(oldfd[INPUT_END]);
		close(oldfd[OUTPUT_END]);
	}
		waitpid(child_pid, &status, 0);
}

static void		end_pipe(t_sh *shell, t_ast *ast, int *fd)
{
	pid_t	child_pid;
	int		status;

	status = 0;
	child_pid = fork();
	if (child_pid == 0)
	{
		close(fd[INPUT_END]);
		dup2(fd[OUTPUT_END], STDIN_FILENO);
		close(fd[INPUT_END]);
		close(fd[OUTPUT_END]);
		exec_pipe_cmd(shell, ast);		
	}
	else
	{
		get_pid(child_pid);
		signal(SIGINT, signal_handler);
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
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		exec_pipe_cmd(shell, ast->right);
	}
	else 
	{
		if (ast->left && ast->left->token == PIPE)
			recurse_pipe(shell, ast->left, fd);
		else if (ast->left)
			end_pipe(shell, ast->left, fd);
		close(fd[OUTPUT_END]);
		close(fd[INPUT_END]);
		get_pid(child_pid);
		signal(SIGINT, signal_handler);
		waitpid(-1, &status, 0);
	}
}