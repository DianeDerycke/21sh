/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:47:01 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/20 16:24:08 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh21.h"

char			*prompt_heredoc(char *end_word)
{
	char	*input;
	char	*tmp;
	int		ret;

	ret = 1;
	input = ft_strdup("");
	while (ret)
	{
		if (!(tmp = line_edition(HEREDOC, NULL)))
			tmp = ft_strdup("");
		if (tmp && ft_strcmp(tmp, "\003") == 0)
			ft_strdel(&input);
		if (tmp && (ft_strcmp(tmp, "\004") == 0 || ft_strcmp(tmp, "\003") == 0))
			break ;
		if (tmp && (ret = ft_strcmp(end_word, tmp)))
		{
			input = ft_strjoin_free(input, tmp);
			input = ft_strjoin_free(input, "\n");
		}
		ft_strdel(&tmp);
	}
	ft_strdel(&tmp);
	return (input);
}

int				handle_heredoc(t_ast *redir)
{
	int		fd[2];

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

static int		apply_heredoc(t_ast *ast)
{
	t_ast	*redir;
	t_ast	*tmp;

	redir = NULL;
	tmp = ast;
	while ((redir = find_next_redir(tmp)))
	{
		if (redir->token == DLESS)
			if (!(redir->heredoc = prompt_heredoc(redir->left->value)))
				return (FAILURE);
		tmp = redir->left;
	}
	return (SUCCESS);
}

int				find_heredoc(t_ast *ast)
{
	int		ret;
	t_ast	*redir;

	redir = NULL;
	ret = 0;
	if (!ast)
		return (SUCCESS);
	if (ast->token == SEPARATOR && ast->right)
		ret = find_heredoc(ast->right);
	else if (ast->token == PIPE)
	{
		ret = find_heredoc(ast->right);
		ret = find_heredoc(ast->left);
	}
	else if (ast->token == WORD || ast->token == DIGIT)
	{
		if (apply_heredoc(ast) == FAILURE)
			return (FAILURE);
	}
	if (ast->token == SEPARATOR && ast->left)
		ret = find_heredoc(ast->left);
	return (ret);
}
