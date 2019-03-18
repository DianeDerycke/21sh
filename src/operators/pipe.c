/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:11:10 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/18 14:44:17 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

static int	handle_heredoc_pipe(t_ast *ast)
{
	t_ast	*redir;
	t_ast	*tmp;

	tmp = ast;
	while ((redir = find_next_redir(tmp)))
	{
		if (redir->token == DLESS)
			return (SUCCESS);
		tmp = tmp->left;
	}
	return (FAILURE);
}

static int	handle_right_cmd(t_sh *shell, t_ast *ast, int *oldfd, int *newfd)
{
	if (handle_heredoc_pipe(ast) == SUCCESS)
	{
		close_pipe(oldfd);
		close_dup(newfd, STDOUT_FILENO);
	}
	else
	{
		if (oldfd)
			close_dup(oldfd, STDIN_FILENO);
		close_dup(newfd, STDOUT_FILENO);
	}
	return (exec_pipe_cmd(shell, ast));
}

static int	end_recurse_pipe(t_sh *shell, t_ast *ast, int *oldfd, int *newfd)
{
	close_pipe(oldfd);
	if (handle_heredoc_pipe(ast) == SUCCESS)
		close_pipe(newfd);
	else
		close_dup(newfd, STDIN_FILENO);
	return (exec_pipe_cmd(shell, ast));
}

static void	recurse_pipe(t_sh *shell, t_ast *ast, int *oldfd, int *fd)
{
	int		newfd[2];
	pid_t	child_pid;
	int		status;

	status = 0;
	if (!fd && pipe(newfd) == ERROR)
		get_error(ERRPIPE, NULL);
	if ((child_pid = fork()) < 0)
		get_error(ERRFORK, NULL);
	if (child_pid == 0)
		fd ? end_recurse_pipe(shell, ast, oldfd, fd) :
			handle_right_cmd(shell, ast->right, oldfd, newfd);
	else
	{
		close_pipe(fd);
		close_pipe(oldfd);
		if (ast->left && ast->left->token == PIPE)
			recurse_pipe(shell, ast->left, newfd, NULL);
		else if (ast->left && ast->token == PIPE)
			recurse_pipe(shell, ast->left, oldfd, newfd);
		sh_push_pidnew(child_pid, &(shell->l_pid));
		signal(SIGINT, signal_handler);
		waitpid(child_pid, &status, 0);
		status != 0 && (ast->std = FAILURE);
	}
}

int			do_pipe(t_sh *shell, t_ast *ast)
{
	shell->fork = 0;
	recurse_pipe(shell, ast, NULL, NULL);
	get_pid_list(shell->l_pid);
	sh_freepidlist(&(shell->l_pid));
	shell->l_pid = NULL;
	while (ast && ast->token == PIPE)
		ast = ast->left;
	return (ast->std);
}
