/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:10:08 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/04 23:53:19 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

t_ast     *find_next_redir(t_ast *ast)
{
    if (!ast)
        return (NULL);
    while (ast)
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
        &redir_lessand,
        &redir_greatand,
    };
    if (!redir->left || (redir->left && 
    ((redir->left->token >= SEPARATOR && redir->left->token <= PIPE) 
    || (redir->left->token >= GREAT && redir->left->token <= GREATAND))))
    {
        syntax_error(redir->left->value);
        exit(1);
    }
    return(redir_array[token](redir, ast));
}

static t_ast    *add_argument_to_cmd(t_ast *ast)
{
    t_ast   *cmd;
    t_ast   *tmp;
    
    cmd = create_elem();
    tmp = cmd;
    while (ast)
    {
        while (ast && ((ast->token == WORD && ast->io_number == 0) || 
        ast->token == DQUOTE || ast->token == SQUOTE || (ast->token == DIGIT && ast->io_number == 0)))
        {
            cmd->value = ft_strdup(ast->value);
            cmd->token = ast->token;
            ast = ast->left;
            cmd->left = create_elem();
            cmd = cmd->left;
        }
        if ((ast = find_next_redir(ast)) && ast->left && ast->left->left)
            ast = ast->left->left;
        else
        {
            while (ast)
            {
                ast = ast->left;
                ast = find_next_redir(ast);
            }
            if (ast)
                ast = ast->left->left;
        }
    }
    cmd = tmp;
    return (cmd);
}

int     exec_redirection(t_ast *ast, t_sh *shell)
{
    pid_t   pid;
    t_ast   *redir;
    int     status;
    t_ast   *tmp;
    t_ast   *cmd;

    tmp = ast;
    cmd = add_argument_to_cmd(ast);
    pid = fork();
    if (pid == 0)
    {
        while ((redir = find_next_redir(tmp)))
        {
            do_redirection(redir->token, redir, ast);
            tmp = redir->left;
        }
        if (cmd)
            just_exec(cmd, shell);
    }
    else
        waitpid(pid, &status, 0);
    return (SUCCESS) ;
}