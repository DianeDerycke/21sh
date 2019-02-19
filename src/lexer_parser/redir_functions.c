/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:26:14 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/19 21:34:56 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int     redir_great(t_ast *redir, t_ast *ast)
{
    int     fd;

    (void)ast;
    // dprintf(2, "REDIR GREAT\n");
    if ((fd = open(redir->left->value,  O_RDWR | O_CREAT | O_TRUNC, 0677)))
    {
        dup2(fd, STDOUT_FILENO);
        close(fd);
        // dprintf(STDOUT_FILENO, "HELLO WRLD\n");
        // dprintf(2,"CMD IS ==> %s\n", redir->left->value);
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

int     get_io_number(t_ast *ast, t_ast *redir)
{
    if (!ast || !redir)
        return (ERROR);
    if (ast == redir)
        return (-2);
    while (ast->left && ast->left != redir)
        ast = ast->left;
    if (ast && ast->token == DIGIT && ast->io_number == 1)
        return (ft_atoi(ast->value));
    return (ERROR);
}

int     redir_greatand(t_ast *redir, t_ast *ast)
{
    int     io_nb;
    int     output;

    // dprintf(2, "REDIR GREATAND\n");
    if (!redir->left)
    {
        printf("21sh: syntax error near unexpected tokan `newline`\n");
        exit (1);
    }
    if (redir->left->token != DIGIT)
    {
        printf("21sh: %s: ambiguous redirect\n", redir->left->value);
        exit (1);
    }
    output = ft_atoi(redir->left->value);
    if ((io_nb = get_io_number(ast, redir)) == -2)
    {
        dup2(1, output);
        close(1);
    }
    else
    {
        // dprintf(2, "OUTPUT ===> %d, IO_NB ===> %d\n", output, io_nb);
        dup2(output, io_nb);
        close(output);
    }
    return (SUCCESS);
}