/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:59:21 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/02/20 15:30:35 by mrandou          ###   ########.fr       */
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

//Try each possibilites on def type array and applies its corresponding action with action_array.
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

char 	*get_valid_input(char **env)
{
	char	*input;
	char	*tmp;

	input = NULL;
	tmp = NULL;
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
