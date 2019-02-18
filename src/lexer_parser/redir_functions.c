/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:26:14 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/18 16:44:18 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int     redir_great(t_ast *redir, t_ast *ast)
{
    int     fd;
    
    (void)ast;
    if ((fd = open(redir->left->value,  O_RDWR | O_CREAT | O_TRUNC, 0677)))
    {
        dup2(fd, 1);
        close(fd);
    }
    return (SUCCESS);
}

int     redir_dgreat(t_ast *redir, t_ast *ast)
{
    int     fd;
    
    (void)ast;
    if ((fd = open(redir->left->value, O_RDWR | O_CREAT | O_APPEND, 0677)))
    {
        dup2(fd, 1);
        close(fd);
    }
    else if (fd == -1)
    {
        ms_no_such_file_or_dir("21sh", redir->left->value);
        exit(1);
    }
    return (SUCCESS);
}

int     redir_less(t_ast *redir, t_ast *ast)
{
    int     fd;
    
    (void)ast;
    if ((fd = open(redir->left->value, O_RDWR)) >= 0)
    {
        dup2(fd, 0);
        close(fd);
    }
    else if (fd == ERROR)
    {
        ms_no_such_file_or_dir("21sh",redir->left->value);
        exit(1);
    }
    return (SUCCESS);
}

int     redir_dless(t_ast *redir, t_ast *ast)
{
    int     fd;
    
    (void)ast;
    if ((fd = open(redir->left->value, O_RDWR | O_APPEND, 0777)))
    {
        dup2(fd, 0);
        close(fd);
    }
    return (SUCCESS);
}

int     redir_greatand(t_ast *redir, t_ast *ast)
{
    int     io_nb;
    int     output;


    io_nb = 2;
    (void)ast;
    if (!redir->left)
    {
        dprintf(2, "21sh: syntax error near unexpected tokan `newline`\n");
        exit (1);
    }
    if (redir->left->token != DIGIT)
    {
        printf("21sh: %s: ambiguous redirect\n", redir->left->value);
        exit (1);
    }
    output = ft_atoi(redir->left->value);
    // if ((io_nb = get_io_number(ast)) == -1)
        if ((io_nb))
    {
        dup2(output, 1);
        close(output);
    }
    else
    {
        dup2(output, io_nb);
        close(output);
    }
    return (SUCCESS);
}