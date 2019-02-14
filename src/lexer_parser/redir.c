/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:10:08 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/14 14:13:02 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int(*redir_array[REDIR_SIZE])(t_ast *) = {
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

static int      do_redirection(int token, t_ast *redir)
{
    return(redir_array[token](redir));
}

int     exec_redirection(t_ast *ast)
{
    t_ast   *redir;
    t_ast   *tmp;
    pid_t   pid;
    t_sh    *shell;
    
    if (!(shell = sh_get_shell(ast)))
        return (FAILURE);
    tmp = ast;
    pid = fork();
    if (pid == 0)
    {
        while ((redir = find_next_redir(tmp)))
        {
            do_redirection(redir->token, redir);
            // add_argument_to_cmd(ast, ast->left);
            tmp = redir;
        }
        just_exec(shell);
    }
    else
        wait(NULL);
    sh_free_shell(shell);
    return (SUCCESS) ;
}