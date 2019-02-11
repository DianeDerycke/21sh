/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 13:41:10 by dideryck          #+#    #+#             */
/*   Updated: 2019/02/11 17:58:27 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int    parser_execution(t_ast *ast)
{
    t_ast     *redir;
    int     ret;

    redir = 0;
    ret = 0;
    if (!ast)
        return (0);
    if (ast->token == SEPARATOR)
        parser_execution(ast->right);
    else if (ast->token == PIPE)
        do_pipe(ast);
    else if (ast->token == WORD)
        ret = exec_cmd(ast);
    if (ast->token != WORD && ast->token != PIPE)
        parser_execution(ast->left);
    return (ret);
}