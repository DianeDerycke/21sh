/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:10:08 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/15 16:18:32 by dideryck         ###   ########.fr       */
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

static int      do_redirection(int token, t_ast *redir)
{
    static int(*redir_array[REDIR_SIZE])(t_ast *) = {
        NULL,
        NULL,
        NULL,
        NULL,
        &redir_great,
        &redir_dgreat,
        &redir_less,
        &redir_dless
        // &redir_and,
        // &redir_lessand,
        // &redir_greatand,
    };
    return(redir_array[token](redir));
}

int     exec_redirection(t_ast *ast, t_sh *shell)
{
    t_ast   *redir;
    int     status;
    int     ret;
    t_ast   *tmp;
    pid_t   pid;

    tmp = ast;
    ret = 0;
    pid = fork();
    if (pid == 0)
    {
        while ((redir = find_next_redir(tmp)))
        {
            // printf("REDIR ===> %s TOKEN IS ===> %d\n", redir->value, redir->token);
            do_redirection(redir->token, redir);
            // add_argument_to_cmd(ast, ast->left);
            tmp = redir->left;
        }
        just_exec(ast, shell);
    }
    else
        waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        return (FAILURE);
    return (SUCCESS) ;
}