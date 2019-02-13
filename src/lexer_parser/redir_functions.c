/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:26:14 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/12 20:38:32 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int     redir_great(t_ast *ast)
{
    int     fd;
    if ((fd = open(ast->left->value,  O_RDWR | O_CREAT | O_TRUNC, 0777)))
    {
        dup2(fd, 1);
        close(fd);
    }
    return (SUCCESS);
}

int     redir_less(t_ast *ast)
{
    int     fd;
    if ((fd = open(ast->left->value, O_RDWR)))
    {
        dup2(fd, 0);
        close(fd);
    }
    return (SUCCESS);
}

int     redir_dless(t_ast *ast)
{
    int     fd;
    if ((fd = open(ast->left->value, O_RDWR | O_APPEND, 0777)))
    {
        dup2(fd, 0);
        close(fd);
    }
    return (SUCCESS);
}

int     redir_and(t_ast *ast)
{
    (void)ast;
    return (SUCCESS);
}

