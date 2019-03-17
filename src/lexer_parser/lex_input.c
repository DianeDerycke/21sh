/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:59:21 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/17 15:57:19 by dideryck         ###   ########.fr       */
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