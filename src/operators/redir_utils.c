/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:11:30 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/20 19:56:47 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/operators.h"
#include "../../includes/lexer_parser.h"

int				get_std_redir(t_ast *ast)
{
	if (ast->token == LESS || ast->token == LESSAND)
		return (ast->std == 0 ? STDIN_FILENO : ast->std);
	if (ast->token == GREATAND)
		return (ast->std == 0 ? STDOUT_FILENO : ast->std);
	if (ast->token == GREAT || ast->token == DGREAT)
		return (STDOUT_FILENO);
	if (ast->token == LESS || ast->token == DLESS)
		return (STDIN_FILENO);
	return (0);
}

t_ast			*find_next_redir(t_ast *ast)
{
	if (!ast)
		return (NULL);
	while (ast)
	{
		if (ast->token >= GREAT && ast->token <= GREATAND)
			return (ast);
		ast = ast->left;
	}
	return (NULL);
}

static t_ast	*get_next_argument(t_ast *ast)
{
	if ((ast = find_next_redir(ast)) && ast->left && ast->left->left)
		ast = ast->left->left;
	else
	{
		while (ast)
		{
			ast = ast->left;
			ast = find_next_redir(ast);
		}
		if (ast)
			ast = ast->left->left;
	}
	return (ast);
}

t_ast			*add_argument_to_cmd(t_ast *ast)
{
	t_ast	*cmd;
	t_ast	*tmp;

	cmd = NULL;
	tmp = NULL;
	while (ast)
	{
		while (ast && ((ast->token == WORD && ast->io_number == 0)
		|| ast->token == DQUOTE || ast->token == SQUOTE
		|| (ast->token == DIGIT && ast->io_number == 0)))
		{
			if (!cmd)
			{
				cmd = create_elem();
				tmp = cmd;
			}
			else if (cmd)
			{
				cmd->left = create_elem();
				cmd = cmd->left;
			}
			cmd->token = ast->token;
			cmd->value = ft_strdup(ast->value);
			ast = ast->left;
		}
		ast = get_next_argument(ast);
	}
	cmd = tmp;
	return (cmd);
}
