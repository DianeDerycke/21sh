/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:11:10 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/04 23:11:19 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

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
			// close(fildes[0]);
			dup2(fildes[1], 1);
			close(fildes[0]);
			parser_execution(ast->right);
		}
		else
		{
			// close(fildes[1]);
			dup2(fildes[0], 0);
			close(fildes[1]);
			waitpid(-1, &status, 0);
			parser_execution(ast->left);
		}
	}
	else
		exit(2);
}