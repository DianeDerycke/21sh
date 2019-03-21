/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 15:50:23 by dideryck          #+#    #+#             */
/*   Updated: 2019/03/21 17:14:29 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer_parser.h"
#include "../../includes/error.h"

static int		is_token_operator(t_ope token)
{
	if (token >= SEPARATOR && token <= GREATAND && token != WORD)
		return (1);
	return (0);
}

static void		add_io_number(t_ast *ast)
{
	if (ast->token == DIGIT
	&& ast->next && (ast->next->token == LESS
	|| ast->next->token == LESSAND || ast->next->token == GREATAND))
		ast->next->std = ft_atoi(ast->value);
}

int				verify_lexer(t_ast *ast)
{
	if (!ast)
		return (FAILURE);
	if ((ast->token == SEPARATOR || ast->token == PIPE))
		return (get_error(UNEXPTOKEN, ast->value));
	while (ast)
	{
		add_io_number(ast);
		if (is_token_operator(ast->token) == 1 && !(ast->next))
			return (get_error(UNEXPTOKEN, ast->value));
		if (is_token_operator(ast->token) == 1 && ast->next &&
			is_token_operator(ast->next->token) == 1)
			return (get_error(UNEXPTOKEN, ast->next->value));
		ast = ast->next;
	}
	return (SUCCESS);
}
