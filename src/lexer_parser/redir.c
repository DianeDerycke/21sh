/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:10:08 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/14 15:49:24 by DERYCKE          ###   ########.fr       */
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
            printf("REDIR ===> %s TOKEN IS ===> %d\n", redir->value, redir->token);
            do_redirection(redir->token, redir);
            // add_argument_to_cmd(ast, ast->left);
            tmp = redir->left;
        }
        just_exec(ast, shell);
    }
    else
        waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        ms_no_such_file_or_dir(tmp->left->value, NULL);
    sh_free_shell(shell);
    return (SUCCESS) ;
}