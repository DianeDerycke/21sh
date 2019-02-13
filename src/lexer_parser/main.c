/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 19:58:42 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/13 17:05:24 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int     main(void)
{
	t_param *param;
	t_ast	*ast;

	while (21)
	{
		param = init_param();
		param->input = get_valid_input();
		hy_history_write(param->input);
		if (lex_input(param) == FAILURE)
			printf("ERROR LEXER\n");
		if (!(ast = create_ast(param->l_tokens, param->l_tokens, NULL)))
			printf("ERROR DURING AST CREATION\n");
		else if (parser_execution(ast) != 0)
			printf("ERROR DURING AST EXECUTION\n");
		free_param(param);
	}
	return (SUCCESS);
}