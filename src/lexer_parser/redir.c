/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:10:08 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/08 19:16:29 by DERYCKE          ###   ########.fr       */
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

static void    reset_std(int *fd)
{
	dup2(fd[OUTPUT_END], STDIN_FILENO);
	close(fd[0]);
	dup2(fd[INPUT_END], STDOUT_FILENO);
	close(fd[INPUT_END]);
}

int     open_file(t_ope token, char *file)
{
    if (token == GREAT || token == LESS)
        return (open(file, O_RDWR | O_CREAT | O_TRUNC, PERM));
    if (token == DGREAT)
        return (open(file, O_RDWR | O_CREAT | O_APPEND, PERM));
    if (token == DLESS)
        return (handle_heredoc(file));
    return (ERROR);
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
    while ((redir = find_next_redir(tmp)))
    {
        if ((fd = open_file(redir->token, redir->left->value)) < 0)
        {
            reset_std(getter_std(0));
            return (get_error(NOFILEDIR, redir->left->value));
        }
        else
        {
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        tmp = redir->left;
    }
    if ((cmd = add_argument_to_cmd(ast)))
        ret = exec_cmd(cmd, shell);
    reset_std(getter_std(0));
    free_ast(&cmd);
    return (ret);
}