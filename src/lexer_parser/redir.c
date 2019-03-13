/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:10:08 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/13 13:36:28 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int         *getter_std(int init)
{
    static int      std[2];

    if (init == 1)
    {
        std[0] = dup(STDIN_FILENO);
        std[1] = dup(STDOUT_FILENO);
    }

    return (std);
}

void    reset_std(int *fd)
{
	dup2(fd[OUTPUT_END], STDIN_FILENO);
	close(fd[0]);
	dup2(fd[INPUT_END], STDOUT_FILENO);
	close(fd[INPUT_END]);
}

static int     open_file(t_ope token, char *file, t_sh *shell)
{
    if (token == GREAT)
        return (open(file, O_RDWR | O_CREAT | O_TRUNC, PERM));
    else if (token == DGREAT)
        return (open(file, O_RDWR | O_CREAT | O_APPEND, PERM));
    else if (token == DLESS)
        return (handle_heredoc(file, shell));
    else
        return (open(file, O_RDWR));
}

int     exec_redirection(t_ast *ast, t_sh *shell)
{
    int     fd;
    t_ast    *cmd;
    t_ast   *redir;
    t_ast   *tmp;
    int     ret;

    ret = 0;
    tmp = ast;
    cmd = NULL;
    while ((redir = find_next_redir(tmp)))
    {
        if ((fd = open_file(redir->token, redir->left->value, shell)) < 0)
        {
            reset_std(getter_std(0));
            if (fd == -2)
                return (FAILURE);
            return (get_error(NOFILEDIR, redir->left->value));
        }
        else
        {
            dup2(fd, get_str_redir(redir->token));
            close(fd);
        }
        tmp = redir->left;
    }
    if (!shell->heredoc && (cmd = add_argument_to_cmd(ast)))
        ret = exec_cmd(cmd, shell);
    reset_std(getter_std(0));
    if (cmd)
        free_ast(&cmd);
    return (ret);
}