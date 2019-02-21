/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:10:08 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/21 15:05:23 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

t_ast     *find_next_redir(t_ast *ast)
{
    if (!ast)
        return (NULL);
    while(ast)
    {
        if (ast->token >= GREAT && ast->token <= GREATAND)
            return (ast);
        ast = ast->left;
    }
    return (NULL);
}

static int      do_redirection(int token, t_ast *redir, t_ast *ast)
{
    static int(*redir_array[REDIR_SIZE])(t_ast *, t_ast *) = {
        NULL,
        NULL,
        NULL,
        &redir_great,
        &redir_dgreat,
        &redir_less,
        &redir_dless,
        NULL,
        NULL,
        &redir_greatand,
        // &redir_lessand,
    };
    return(redir_array[token](redir, ast));
}

int     exec_redirection(t_ast *ast, t_sh *shell)
{
    t_ast   *redir;
    int     status;
    t_ast   *tmp;
    pid_t   pid;

    tmp = ast;
    pid = fork();
    if (pid == 0)
    {
        while ((redir = find_next_redir(tmp)))
        {
            do_redirection(redir->token, redir, ast);
            // add_argument_to_cmd(ast, ast->left);
            tmp = redir->left;
        }
        if (ast->token == WORD)
        {
            just_exec(ast, shell);
            exit (1);
        }
    }
    else
        waitpid(pid, &status, 0);
    return (SUCCESS) ;
}