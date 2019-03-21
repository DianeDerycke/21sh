/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 13:41:10 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/21 16:49:34 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer_parser.h"
#include "../../includes/execution.h"
#include "../../includes/operators.h"

int		parser_execution(t_ast *ast, t_sh *shell)
{
	int		ret;

	ret = 0;
	if (!ast)
		return (SUCCESS);
	if (ast->token == SEPARATOR && ast->right)
		ret = parser_execution(ast->right, shell);
	else if (ast->token == PIPE)
		return (do_pipe(shell, ast));
	else if (find_next_redir(ast))
	{
		shell->fork = 1;
		getter_std(1);
		ret = exec_redirection(ast, shell);
	}
	else if (ast->token >= WORD)
	{
		shell->fork = 1;
		ret = exec_cmd(ast, shell);
	}
	if (ast->token == SEPARATOR && ast->left)
		ret = parser_execution(ast->left, shell);
	return (ret);
}
