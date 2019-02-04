/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 19:58:42 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/04 23:36:41 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int(*def_type[ARRAY_SIZE])(int) = {
	&ft_is_whitespace,
	&ft_is_single_quote,
	&ft_is_double_quote,
	&ft_isdigit,
	&ft_is_operator,
	&ft_isidentifier
};

int(*action[ARRAY_SIZE])(t_param *) = {
	&whitespace_action,
	&single_quote_action,
	&double_quote_action,
	&digit_action, //fix digit action ex : ls > 1ppppp
	&operator_action,
	&identifier_action
};

//Try each possibilites on def type array and applies its corresponding action with action array.
int     lex_input(t_param *param)
{
	int i = 0;

	if (!param || !(param->input))
		return (FAILURE);
	while (param->input[param->index])
	{
		while (i < ARRAY_SIZE && (def_type[i](param->input[param->index])) == 0)
			i++;
		if (i == ARRAY_SIZE)
			return (FAILURE);
		if (def_type[i](param->input[param->index]))
		{
			param->ft = def_type[i];
			if ((action[i](param)) == FAILURE)
				return (FAILURE);
		}
		i = 0;
	}
	return (SUCCESS);
}

//to do : handle \n case
static int     loop_input(t_param *param)
{
	int     ret;
	t_ast *ast;
	char    *tmp;

	ret = 0;
	tmp = NULL;
	if (!(param = malloc(sizeof(t_param))))
		return (FAILURE);
	init_param(&param);
	while (21)
	{
		if (!(param->input = line_edition(0)))
			continue ;
		while (!tmp && (ret = valid_quotes(param->input)))
		{
			if (!(tmp = line_edition(ret)))
				continue;
			param->input = ft_strjoin_free(param->input, "\n");
			param->input = ft_strjoin(param->input, tmp);
			ft_strdel(&tmp);
		}
		hy_history_write(param->input);
		if (lex_input(param)== FAILURE) //Display error if something went wrong on the lexer
		{
			printf("ERROR LEX\n");
			return (FAILURE);
		}
		// else
		// 	display_list(param->l_tokens);
		if (!(ast = parser_input(param->l_tokens, param->l_tokens, NULL)))
			return (FAILURE);
		else
        {
		// 	display_tree(ast, 0, 0);
            if (parser_execution(ast) != 0)
				printf("error execution\n");
        }
		ft_strdel(&param->input);
		init_param(&param);
	}
    free(param);
	return (SUCCESS);
}

int     main(void)
{
	t_param param;
	if (loop_input(&param) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}