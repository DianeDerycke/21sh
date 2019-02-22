/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:26:14 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/22 17:20:24 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

int     redir_great(t_ast *redir, t_ast *ast)
{
    int     fd;

    (void)ast;
    if ((fd = open(redir->left->value,  O_RDWR | O_CREAT | O_TRUNC, 0677)))
        dup2(fd, STDOUT_FILENO);
    if (ast == redir)
        exit (1);
    return (SUCCESS);
}

int     redir_dgreat(t_ast *redir, t_ast *ast)
{
    int     fd;
    
    (void)ast;
    if ((fd = open(redir->left->value, O_RDWR | O_CREAT | O_APPEND, 0677)))
        dup2(fd, 1);
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
        dup2(fd, 0);
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
        dup2(fd, 0);
    return (SUCCESS);
}

int     get_io_number(t_ast *ast, t_ast *redir)
{
    if (!ast || !redir)
        return (ERROR);
    if (ast == redir)
        return (1);
    while (ast->left && ast->left != redir)
        ast = ast->left;
    if (ast && ast->token == DIGIT && ast->io_number == 1)
        return (ft_atoi(ast->value));
    return (ERROR);
}

static int     get_dest_fd(char *arg, int *is_close)
{
    int     i;
    int     dest;
    char    *tmp;

    i = 0;
    dest = 0;
    tmp = NULL;
    while(arg[i] && ft_isdigit(arg[i]))
        i++;
    if (arg[i] && (arg[i] != '-' || (ft_strlen(arg) - (i + 1)) > 0))
        return (ERROR);
    if (arg[i] == '-' && !arg[i + 1])
        *is_close = 1;
    if (!(tmp = ft_strndup(arg, i)))
        return (ERROR);
    dest = ft_atoi(tmp);
    ft_strdel(&tmp);
    return(dest);
}

int     redir_greatand(t_ast *redir, t_ast *ast)
{
    int     io_nb;
    int     output;
    int     is_close;

    if (!redir->left)
    {
        syntax_error(NULL);
        exit (1);
    }
    if ((output = get_dest_fd(redir->left->value, &is_close)) == ERROR)
    {
        ambiguous_redirect(redir->left->value);
        exit (1);
    }
    if ((io_nb = get_io_number(ast, redir)) == ERROR)
        exit (1);
    dup2(output, io_nb);
    if (is_close == 1)
        close(io_nb);
    return (SUCCESS);
}