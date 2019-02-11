/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:10:08 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/10 21:24:09 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int(*do_redir[ARRAY_SIZE])(t_ast *) = {
    &redir_great
};

int     redir_great(t_ast *ast)
{
    int     fd;
    if ((fd = open(ast->left->value, O_RDWR, O_CREAT)))
        dup2(fd, 1);
    return (SUCCESS);
}

t_ast     *find_redir(t_ast *ast)
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

int     exec_redirection(t_ast *ast)
{
    t_ast   *redir;

    while ((redir = find_redir(ast)))
    {
        if (redir->token == GREAT)
            redir_great(redir);

    }
    return (SUCCESS) ;
}