/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:10:08 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/13 12:52:53 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int(*do_redir[REDIR_SIZE])(t_ast *) = {
    NULL,
    NULL,
    NULL,
    NULL,
    &redir_great,
    &redir_less,
    &redir_dless
    // &redir_and,
    // &redir_lessand,
    // &redir_greatand,
};

t_ast     *find_next_redir(t_ast *ast)
{
    if (!ast)
        return (NULL);
    if (ast->token >= GREAT && ast->token <= GREATAND)
        ast = ast->left;
    while(ast)
    {
        if (ast->token >= GREAT && ast->token <= GREATAND)
            return (ast);
        ast = ast->left;
    }
    return (NULL);
}

int     exec_redirection(t_ast *ast)
{
    t_ast   *redir;
    pid_t   pid;
    t_ope   token;
    t_sh    *shell;
    
    if (!(shell = sh_get_shell(ast)))
        return (FAILURE);
    if (!(redir = find_next_redir(ast)))
        return (SUCCESS);
    token = redir->token;
    pid = fork();
    if (pid == 0)
    {
        if (redir->token == GREAT)
            do_redir[redir->token](ast->left);
        just_exec(shell);
    }
    else
        wait(NULL);
    sh_free_shell(shell);
    exec_redirection(redir);
    return (SUCCESS) ;
}