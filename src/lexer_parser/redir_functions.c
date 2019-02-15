/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:26:14 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/15 17:39:06 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int     redir_great(t_ast *ast)
{
    int     fd;
    if ((fd = open(ast->left->value,  O_RDWR | O_CREAT | O_TRUNC, 0677)))
    {
        dup2(fd, 1);
        close(fd);
    }
    return (SUCCESS);
}

int     redir_dgreat(t_ast *ast)
{
    int     fd;
    if ((fd = open(ast->left->value, O_RDWR | O_CREAT | O_APPEND, 0677)))
    {
        dup2(fd, 1);
        close(fd);
    }
    else if (fd == -1)
    {
        ms_no_such_file_or_dir("21sh", ast->left->value);
        exit(1);
    }
    return (SUCCESS);
}

int     redir_less(t_ast *ast)
{
    int     fd;
    if ((fd = open(ast->left->value, O_RDWR)) >= 0)
    {
        dup2(fd, 0);
        close(fd);
    }
    else if (fd == ERROR)
    {
        ms_no_such_file_or_dir("21sh",ast->left->value);
        exit(1);
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