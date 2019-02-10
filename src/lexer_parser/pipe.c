/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:11:10 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/10 02:55:22 by DERYCKE          ###   ########.fr       */
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

	if (!ast)
		return (FAILURE);
    if (!(shell = sh_get_shell(ast)))
        return (FAILURE);
    apply_expansions(shell);
    if ((exec_builtin(shell)) == FAILURE)
		if (just_exec(shell) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}

// void    do_pipe(t_ast *ast)
// {
//     int		fd[2];
// 	int		pipe_ret;
// 	// int 	status;
// 	pid_t	pid;
// 	pid_t 	pid2;

// 	pipe_ret = pipe(fd);
// 	if (pipe_ret == -1)
// 		exit (2);
// 	if (pipe_ret == 0)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			close(fd[OUTPUT_END]);
// 			dup2(fd[INPUT_END], STDOUT_FILENO);
// 			close(fd[INPUT_END]);
// 			exec_pipe_cmd(ast->right);
// 		}
// 	}
// 		pid2 = fork();
// 		if (pid2 == -1)
// 			exit (2);
// 		if (pid2 == 0)
// 		{
// 			close(fd[INPUT_END]);
// 			dup2(fd[OUTPUT_END], STDIN_FILENO);
// 			close(fd[OUTPUT_END]);
// 			exec_pipe_cmd(ast->left);
// 		}
// 	close(fd[OUTPUT_END]);
// 	close(fd[INPUT_END]);
// 	wait(NULL);
// }

// static void		do_process2(t_ast *ast, int fd[])
// {
// 	pid_t	child_pid;
// 	int 	status;
	
// 	child_pid = fork();
// 	if (child_pid == -1)
// 		exit(2);
// 	if (child_pid == 0)
// 	{
// 		close(fd[INPUT_END]);
// 		dup2(fd[OUTPUT_END], STDIN_FILENO);
// 		close(fd[OUTPUT_END]);
// 		dprintf(2,"CHILD 3\n");
// 		exec_pipe_cmd(ast->left);
// 	}
// 	else
// 	{
// 		close(fd[OUTPUT_END]);
// 		close(fd[INPUT_END]);
// 		waitpid(child_pid, &status, 0);
// 	}
// 	dprintf(2,"END CHILD 3\n");
// }

// void	connect_pipe1_to_pipe2(int fd[], int fd2[])
// {
// 	int		pipe_ret;

// 	pipe_ret = pipe(fd2);
// 	if (pipe_ret == -1)
// 		exit (1);
// 	dup2(fd[0], fd2[0]);
// 	close(fd[0]);
// 	(close(fd2[0]));
// 	dup2(fd[1], fd2[1]);
// 	close(fd[1]);
// 	close(fd2[1]);
// }

void		do_process(t_ast *ast, int fd[], int state)
{
	pid_t	child_pid;
	pid_t	p2;
	int		status;
	int		fd2[2];
	
	(void)state;
	if (!ast)
		return ;
	child_pid = fork();
	if (child_pid == -1)
		exit(1);
	if (child_pid == 0)
	{
		// dprintf(2,"CHILD 1\n");
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		exec_pipe_cmd(ast->right);
	}
	if (ast->left && ast->left->token == PIPE)
	{
		if (pipe(fd2) == -1)
			exit (2);
		p2 = fork();
		if (p2 == 0)
		{
			// dprintf(2,"CHILD 2\n");
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			close(fd2[0]);
			dup2(fd2[1], 1);
			close(fd2[1]);
			exec_pipe_cmd(ast->left->right);
		}		
	}
	if (ast->left->left)
	{
		pid_t p3;
		p3 = fork();
		// dprintf(2, "CMD CHILD 3 ===> %s\n", ast->left->left->value);
		if (p3 == 0)
		{
			// dprintf(2,"CHILD 3\n");
			close(fd2[1]);
			dup2(fd2[0], 0);
			close(fd2[0]);
			close(fd[0]);
			close(fd[1]);
			exec_pipe_cmd(ast->left->left);
		}
	}
	close(fd[OUTPUT_END]);
	close(fd[INPUT_END]);
	close(fd2[INPUT_END]);
	close(fd2[OUTPUT_END]);
	waitpid(-1, &status, 0);
}

int 	do_pipe(t_ast *ast)
{
	int		fd[2];
	int		pipe_ret;

	pipe_ret = pipe(fd);
	if (pipe_ret == -1)
		return (FAILURE);
	do_process(ast, fd, 0);
	return (SUCCESS);
}