/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 13:41:10 by dideryck          #+#    #+#             */
/*   Updated: 2019/02/19 18:02:30 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int    parser_execution(t_ast *ast, t_sh *shell)
{
    t_ast     *redir;
    int     ret;

    redir = 0;
    ret = 0;
    if (!ast)
        return (0);
    if (ast->token == SEPARATOR)
        parser_execution(ast->right, shell);
    else if (ast->token == PIPE)
        do_pipe(ast, shell);
    else if (ast->token == WORD || ast->token == DIGIT || 
        (ast->token >= GREAT && ast->token <= GREATAND))
    {
        if (find_next_redir(ast))
            ret = exec_redirection(ast, shell);
        else
            ret = exec_cmd(ast, shell);
    }
    if (ast->token == SEPARATOR)
        parser_execution(ast->left, shell);
    return (ret);
}