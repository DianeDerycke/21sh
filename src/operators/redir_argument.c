/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:11:30 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/21 17:56:16 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/operators.h"
#include "../../includes/lexer_parser.h"

static int		is_argument(t_ast *ast)
{
	if ((ast->token == WORD && ast->io_number == 0)
		|| ast->token == DQUOTE || ast->token == SQUOTE
		|| (ast->token == DIGIT && ast->io_number == 0))
		return (SUCCESS);
	return (FAILURE);
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

static t_ast	*create_new_argument(t_ope token, char *value)
{
	t_ast	*new;

	if (!(new = create_elem()))
		return (NULL);
	new->token = token;
	new->value = ft_strdup(value);
	return (new);
}

t_ast			*add_argument_to_cmd(t_ast *ast)
{
	t_ast	*cmd;
	t_ast	*tmp;

	cmd = NULL;
	tmp = NULL;
	while (ast)
	{
		while (ast && is_argument(ast) == SUCCESS)
		{
			if (!cmd)
			{
				cmd = create_new_argument(ast->token, ast->value);
				tmp = cmd;
			}
			else
			{
				cmd->left = create_new_argument(ast->token, ast->value);
				cmd = cmd->left;
			}
			ast = ast->left;
		}
		ast = get_next_argument(ast);
	}
	cmd = tmp;
	return (cmd);
}
