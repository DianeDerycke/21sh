/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:59:21 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/20 18:29:46 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"


static int		getter_type_input(int c, int index, t_param *param)
{
	static int(*def_type[ARRAY_SIZE])(int) = 
	{
		&ft_is_whitespace,
		&ft_is_single_quote,
		&ft_is_double_quote,
		&ft_isdigit,
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
		&digit_action, //fix digit action ex : ls > 1ppppp
		&operator_action,
		&identifier_action
	};
	return (action[index](param));
}

int     lex_input(t_param *param)
{
	int i = 0;

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
			if (getter_action(param, i) == FAILURE)
				return (FAILURE);
		i = 0;
	}
	return (SUCCESS);
}

char 	*get_valid_input(char **env)
{
	char	*input;

	while (21)
	{
		if (!(input = line_edition(0, env)))
			continue;
		handle_quotes(&input);
		if (input)
			break ;
	}
	return (input);
}
