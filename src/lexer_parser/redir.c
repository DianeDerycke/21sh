/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:10:08 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/14 16:53:27 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int         *getter_std(int init)
{
    static int      std[3];

    if (init == 1)
    {
        std[0] = dup(STDIN_FILENO);
        std[1] = dup(STDOUT_FILENO);
        std[2] = dup(STDERR_FILENO);
    }

    return (std);
}

void    reset_std(int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
    dup2(fd[2], STDERR_FILENO);
    close(fd[2]);
}

static int     open_file(t_ope token, char *file, t_ast *redir, t_ast *ast)
{
    if (token == GREAT)
        return (open(file, O_RDWR | O_CREAT | O_TRUNC, PERM));
    else if (token == DGREAT)
        return (open(file, O_RDWR | O_CREAT | O_APPEND, PERM));
    else if (token == DLESS)
        return (handle_heredoc(redir));
    else if (token == LESSAND || token == GREATAND)
        return (handle_agregation(redir, ast));
    else
        return (open(file, O_RDWR));
}

static int      do_redirection(t_ast *redir, t_ast *ast)
{
    int         fd;

    if ((fd = open_file(redir->token, redir->left->value, redir, ast)) < 0)
    {
        reset_std(getter_std(0));
        if (fd == -2)
            return (FAILURE);
        return (get_error(NOFILEDIR, redir->left->value));
    }
    if (redir->token != LESSAND && redir->token != GREATAND)
    {
        dup2(fd, get_str_redir(redir->token));
        close(fd);
    }
    return (SUCCESS);
}

int     exec_redirection(t_ast *ast, t_sh *shell)
{
    t_ast    *cmd;
    t_ast   *redir;
    t_ast   *tmp;
    int     ret;

    cmd = NULL;
    tmp = ast;
    ret = 0;
    while ((redir = find_next_redir(tmp)))
    {
        if (do_redirection(redir, ast) == FAILURE)
            return (FAILURE);
        tmp = redir->left;
    }
    if ((cmd = add_argument_to_cmd(ast)))
        ret = exec_cmd(cmd, shell);
    if (cmd)
        free_ast(&cmd);
    reset_std(getter_std(0));
    return (ret);
}