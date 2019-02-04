/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:10:08 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/04 23:10:41 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

int     find_redir(t_ast *ast)
{
    if (!ast)
        return (FAILURE);
    while(ast)
    {
        if (ast->token >= GREAT && ast->token <= GREATAND)
            return (SUCCESS);
        ast = ast->left;
    }
    return (FAILURE);
}

void    exec_redirection(t_ast *ast)
{
    (void)ast;
    return ;
}