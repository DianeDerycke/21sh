/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:10:08 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/07 03:57:26 by DERYCKE          ###   ########.fr       */
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

static t_ast    *get_next_argument(t_ast *ast)
{
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
    return (ast);
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
        ast->token == DQUOTE || ast->token == SQUOTE || 
        (ast->token == DIGIT && ast->io_number == 0)))
        {
            cmd->value = ft_strdup(ast->value);
            cmd->token = ast->token;
            ast = ast->left;
            cmd->left = create_elem();
            cmd = cmd->left;
        }
        ast = get_next_argument(ast);
    }
    cmd = tmp;
    return (cmd);
}

static int      do_redirection(t_ast *redir, t_ast *ast)
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

    return(redir_array[redir->token](redir, ast));
}

int     exec_redirection(t_ast *ast, t_sh *shell)
{
    t_ast   *redir;
    t_ast   *tmp;
    int     ret;

    ret = 0;
    tmp = ast;
    while ((redir = find_next_redir(tmp)))
    {
        if (do_redirection(redir, ast) == FAILURE)
            return (FAILURE);
        tmp = redir->left;
    }
    if (!(tmp = add_argument_to_cmd(ast)))
        return (FAILURE);
    shell->fork = 1;
    ret = exec_cmd(tmp, shell);
    redir = find_next_redir(ast);
    while (redir)
    {
        dup2(redir->to, redir->std);
        close(redir->to);
        close(redir->from);
        ast = ast->next;
        redir = find_next_redir(ast);
    }
    free_ast(&tmp);
    return (ret);
}