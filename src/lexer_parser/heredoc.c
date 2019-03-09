/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:47:01 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/09 15:46:11 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

char    *prompt_heredoc(char *end_word)
{
    char    *input;
    char    *tmp;
    int     ret;

    ret = 1;
    input = ft_strdup("");
    tmp = NULL;
    while (ret)
    {
        tmp = line_edition(HEREDOC, NULL);
        if (tmp && ((ft_strcmp(tmp, "\004") == 0) || (ft_strcmp(tmp, "\003") == 0)))
        {
            ft_strdel(&tmp);
            return (NULL);
        }
        if (tmp)
            ret = ft_strcmp(end_word, tmp);
        if (ret)
        {
            input = ft_strjoin_free(input, tmp);
            input = ft_strjoin_free(input, "\n");
        }
        ft_strdel(&tmp);
    }
    ft_strdel(&tmp);
    return(input);
}

int     handle_heredoc(char *file)
{
    char    *content;
    int     fd[2];

    if (!(content = prompt_heredoc(file)))
        return (-2);
    if (pipe(fd) < 0)
        return (ERROR);
    if (fork() == 0)
    {
        close(fd[OUTPUT_END]);
        ft_putstr_fd(content, fd[INPUT_END]);
        ft_strdel(&content);
        exit(0);
    }
        wait(NULL);
        close(fd[INPUT_END]);
    return (fd[OUTPUT_END]);
}