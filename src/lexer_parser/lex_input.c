/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:59:21 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/17 03:11:19 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer_parser.h"
#include "../../includes/error.h"

static int		getter_type_input(int c, int index, t_param *param)
{
	static int(*def_type[ARRAY_SIZE])(int) = 
	{
		&ft_is_whitespace,
		&ft_is_single_quote,
		&ft_is_double_quote,
		&ft_is_operator,
		&ft_isidentifier
	};
	param->ft = def_type[index];
	return (def_type[index](c));
}

static int		getter_action(t_param *param, int index)
{
	static int	(*action[ARRAY_SIZE])(t_param *) = 
	{
		&whitespace_action,
		&single_quote_action,
		&double_quote_action,
		&operator_action,
		&identifier_action
	};
	return (action[index](param));
}

int     lex_input(t_param *param)
{
	int 	i;
	int		ret;

	i = 0;
	ret = 0;
	if (!param || !(param->input))
		return (FAILURE);
	while (param->input[param->index])
	{
		while (i < ARRAY_SIZE && 
			(getter_type_input(param->input[param->index], i, param)) == 0)
			i++;
		if (i == ARRAY_SIZE)
			return (FAILURE);
		if (getter_type_input(param->input[param->index], i, param))
			if ((ret = getter_action(param, i)) != SUCCESS)
				return (get_error(ret, param->input + param->index));
		i = 0;
	}
	return (SUCCESS);
}

static int		is_token_operator(t_ope token)
{
	if (token >= SEPARATOR && token <= GREATAND && token != WORD)
		return (1);
	return (0);
}

int		verify_lexer(t_ast *ast)
{
	if (!ast)
		return (FAILURE);
	if ((ast->token == SEPARATOR || ast->token == PIPE) && !ast->next)
		return (get_error(UNEXPTOKEN, ast->value));
	while (ast)
	{
		if (is_token_operator(ast->token) == 1 && !(ast->next))
			return (get_error(UNEXPTOKEN, ast->value));
		if (is_token_operator(ast->token) == 1 && ast->next &&
			is_token_operator(ast->next->token) == 1)
			return (get_error(UNEXPTOKEN, ast->next->value));
		ast = ast->next;
	}
	return (SUCCESS);
}
