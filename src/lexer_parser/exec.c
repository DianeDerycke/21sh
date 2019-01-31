/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 19:03:52 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/01/31 10:38:46 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int     find_redir(t_ast *ast)
{
    if (!ast)
        return (FAILURE);
    while(ast)
    {
        if (ast->token >= GREAT && ast->token <= GREATAND)
            return (SUCCESS);
        ast = ast->left;
    }
    return (FAILURE);
}

void    exec_redirection(t_ast *ast)
{
    (void)ast;
    return ;
}

// static void		exec_pipe2(t_ast *ast)
// {
// 	dup2(0, 1);
// 	exec_cmd(ast->right);
// 	dup2(1, 0);
// 	parser_execution(ast->left);
// }

void    exec_pipe(t_ast *ast)
{
    int		fildes[2];
	pid_t	pid;
	int		status;

	status = 0;
	// if (ast->right && find_builtin(ast->right->value) == SUCCESS)
		// exec_pipe2(ast);
	if (pipe(fildes) == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			close(fildes[0]);
			dup2(fildes[1], 1);
            close(fildes[0]);
			if (ast->right)
				ast->right->pipecall = 1;
			parser_execution(ast->right);
		}
		else
		{
			close(fildes[1]);
			dup2(fildes[0], 0);
            close(fildes[1]);
			waitpid(-1, &status, 0);
			if (ast->left)
				ast->left->pipecall = 0;
			parser_execution(ast->left);
		}
	}
	else
		exit(2);
}
