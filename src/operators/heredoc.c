/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:47:01 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/17 04:03:48 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

//NORME 2 FT

char    *prompt_heredoc(char *end_word)
{
    char    *input;
    char    *tmp;
    int     ret;

    ret = 1;
    input = ft_strdup("");
    while (ret)
    {
        if (!(tmp = line_edition(HEREDOC, NULL)))
			tmp = ft_strdup("");
        if (tmp && ft_strcmp(tmp, "\004") == 0)
        {
            ft_strdel(&tmp);
            return (input);
		}
		if (tmp && ft_strcmp(tmp, "\003") == 0)
		{
			ft_strdel(&input);
			ft_strdel(&tmp);
			return (NULL);
		}
        if (tmp)
            ret = ft_strcmp(end_word, tmp);
        if (ret != 0)
        {
            input = ft_strjoin_free(input, tmp);
            input = ft_strjoin_free(input, "\n");
        }
        ft_strdel(&tmp);
    }
    ft_strdel(&tmp);
    return(input);
}

int     handle_heredoc(t_ast *redir)
{
    int     fd[2];

    if (pipe(fd) < 0)
        return (ERROR);
    if (fork() == 0)
    {
        close(fd[OUTPUT_END]);
        ft_putstr_fd(redir->heredoc, fd[INPUT_END]);
        exit(0);
    }
        wait(NULL);
        close(fd[INPUT_END]);
    return (fd[OUTPUT_END]);
}

int     apply_heredoc(t_ast *ast)
{
    int     ret;
    t_ast   *redir;
    t_ast   *tmp;

    redir = NULL;
    ret = 0;
    if (!ast)
        return (SUCCESS);
    if (ast->token == SEPARATOR && ast->right)
        ret = apply_heredoc(ast->right);
    else if (ast->token == PIPE)
    {
        ret = apply_heredoc(ast->right);
        ret = apply_heredoc(ast->left);
    }
    else if (ast->token == WORD)
    {
        tmp = ast;
        while ((redir = find_next_redir(tmp)))
        {
            if (redir->token == DLESS)
                if (!(redir->heredoc = prompt_heredoc(redir->left->value)))
                    return (FAILURE);
            tmp = redir->left;
        }
    }
    if (ast->token == SEPARATOR && ast->left)
        ret = apply_heredoc(ast->left);
    return (ret);
}
