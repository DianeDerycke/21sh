/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 19:58:42 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/04 18:28:45 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

static int 	process_input(t_param *param, t_sh *shell)
{
	t_ast *ast;

	ast = NULL;
	// display_list(param->l_tokens);
	// display_tree(ast, 0, 0);
	if (lex_input(param) != SUCCESS)
		return (FAILURE);
	else if (!(ast = create_ast(param->l_tokens, param->l_tokens, NULL)))
		return (FAILURE);
	else if (ast && parser_execution(ast, shell) != 0)
		return (FAILURE);
	return (SUCCESS);
}

int     main(void)
{
	t_param *param;
	t_sh	*shell;
	int		ret;

	ret = 0;
	shell = init_shell();
	while (21)
	{
		param = init_param();
		param->input = get_valid_input(shell->env, ret);
		hy_history_write(param->input, shell->env);
		ret = process_input(param, shell);
		free_param(param);
		if (!isatty(0))
			break;
	}
	sh_free_shell(shell);
	return (ret);
}
