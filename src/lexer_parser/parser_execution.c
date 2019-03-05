/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 13:41:10 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/05 12:56:27 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int    parser_execution(t_ast *ast, t_sh *shell)
{
    int     ret;

    ret = 0;
    if (!ast)
        return (0);
    if (ast->token == SEPARATOR && ast->right)
        ret = parser_execution(ast->right, shell);
    else if (ast->token == PIPE)
    {
        ret = recurse_pipe(shell, ast, NULL, NULL);
        sh_freepidlist(&shell->l_pid);
        shell->l_pid = NULL;
    }
    else if (ast->token >= WORD)
    {
        if (find_next_redir(ast))
            ret = exec_redirection(ast, shell);
        else
            ret = exec_cmd(ast, shell);
    }
    if (ast->token == SEPARATOR && ast->left)
        ret = parser_execution(ast->left, shell);
    return (ret);
}