/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 19:58:42 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/18 14:58:08 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int     main(void)
{
	t_param *param;
	t_ast	*ast;
	t_sh	*shell;
	int		ret;

	ret = 0;
	while (21)
	{
		param = init_param();
		param->input = get_valid_input();
		shell = init_shell();
		hy_history_write(param->input);
		if (lex_input(param) == FAILURE)
			printf("ERROR LEXER\n");
		if (!(ast = create_ast(param->l_tokens, param->l_tokens, NULL)))
			ret = FAILURE;
		// display_tree(ast, 0, 0);
		if (ast && parser_execution(ast, shell) != 0)
			ret = FAILURE;
		free_param(param);
	}
	return (ret);
}