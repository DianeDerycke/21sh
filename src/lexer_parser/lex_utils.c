/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 19:55:35 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/22 15:19:11 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer_parser.h"

t_param		*get_param(t_param *param)
{
	static t_param		*to_free;

	if (param)
		to_free = param;
	return (to_free);
}

char	*get_operator(int index)
{
	static char		operators[20][20] = {
		{";"},
		{"|"},
		{"\n"},
		{">"},
		{">>"},
		{"<"},
		{"<<"},
		{"&"},
		{"<&"},
		{">&"},
		{"\0"},
	};

	return (operators[index]);
}

int		get_ast_op(char *c, int length)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (!c)
		return (FAILURE);
	while (i < 10)
	{
		tmp = get_operator(i);
		if (ft_strncmp(c, tmp, length) == 0)
			break ;
		i++;
	}
	return (i == 10 ? -1 : i);
}

char	*copy_until_array_ft(char *s, int *start, int (*array[2])(int))
{
	char	*tmp;
	int		length;
	int		i;

	i = 0;
	tmp = NULL;
	length = 0;
	while (s[length])
	{
		i = 0;
		while (i < SIZE_CONDITION)
		{
			if (!array[i](s[length]))
				return (NULL);
			i++;
		}
		length++;
	}
	if (!(tmp = ft_strndup(s, length)))
		return (NULL);
	*start += length;
	return (tmp);
}

int		whitespace_action(t_param *param)
{
	param->index++;
	return (SUCCESS);
}

int		push_node(char *value, int token, t_ast **node, int io_nb)
{
	t_ast	*tmp;

	if (!node || !*node)
	{
		if (!(*node = create_elem()))
			return (FAILURE);
		if (!((*node)->value = ft_strdup(value)))
			return (FAILURE);
		(*node)->token = token;
		(*node)->io_number = io_nb;
	}
	else
	{
		tmp = *node;
		while ((*node)->next)
			(*node) = (*node)->next;
		if (!((*node)->next = create_elem()))
			return (FAILURE);
		if (!((*node)->next->value = ft_strdup(value)))
			return (FAILURE);
		(*node)->next->token = token;
		(*node)->next->io_number = io_nb;
		*node = tmp;
	}
	return (SUCCESS);
}
