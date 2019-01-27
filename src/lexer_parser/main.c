/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 19:58:42 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/01/24 16:38:33 by mrandou          ###   ########.fr       */
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
	t_token *ast;
	char    *tmp;

	ret = 0;
	tmp = NULL;
	if (!(param = malloc(sizeof(t_param))))
		return (FAILURE);
	init_param(&param);
	while (21)
	{
		if (!(param->input = line_edition()))
			continue ;
		if (ft_strcmp(param->input, "exit") == SUCCESS)
			exit(0);
		while ((ret = valid_quotes(param->input)))
		{
			if (ret == 1)
				ft_putstr("quote>");
			if (ret == 2)
				ft_putstr("dquote>");
			tmp = line_edition();
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
		else
			display_list(param->l_tokens);
		if (!(ast = parser_input(param->l_tokens, NULL)))
			return (FAILURE);
		else
			display_tree(ast, 0, 0);
		ft_strdel(&param->input);
		free(param);
		if (!(param = malloc(sizeof(t_param))))
			return (FAILURE);
		init_param(&param);
	}
	return (SUCCESS);
}

int     main(void)
{
	t_param param;
	if (loop_input(&param) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
