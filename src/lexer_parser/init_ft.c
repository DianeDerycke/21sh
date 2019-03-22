/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 00:15:46 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/22 15:20:00 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer_parser.h"

void		free_ast(t_ast **ast)
{
	t_ast *tmp;

	tmp = NULL;
	if (!ast || !(*ast))
		return ;
	while (*ast)
	{
		tmp = *ast;
		(*ast) = (*ast)->left;
		ft_strdel(&(tmp->value));
		tmp->token = 0;
		tmp->io_number = 0;
		tmp->next = NULL;
		tmp->right = NULL;
		tmp->left = NULL;
		free(tmp);
		tmp = NULL;
	}
	ast = NULL;
}

void		free_lexer(t_ast **ast)
{
	t_ast *tmp;

	if (!ast || !*ast)
		return ;
	while (*ast)
	{
		tmp = *ast;
		(*ast) = (*ast)->next;
		ft_strdel(&(tmp->value));
		ft_strdel(&(tmp->heredoc));
		tmp->token = 0;
		tmp->io_number = 0;
		tmp->next = NULL;
		tmp->right = NULL;
		tmp->left = NULL;
		free(tmp);
		tmp = NULL;
	}
	ast = NULL;
}

void		free_param(t_param *param)
{
	ft_strdel(&(param->input));
	param->input = NULL;
	param->index = 0;
	param->token = 0;
	param->ft = NULL;
	free_lexer(&param->l_tokens);
	free(param);
	param = NULL;
}

t_param		*init_param(void)
{
	t_param *new;

	if (!(new = malloc(sizeof(t_param))))
		sh_malloc_error();
	new->input = NULL;
	new->index = 0;
	new->token = 0;
	new->ft = NULL;
	new->l_tokens = NULL;
	get_param(new);
	return (new);
}

t_ast		*create_elem(void)
{
	t_ast	*new;

	if (!(new = malloc(sizeof(t_ast))))
		ft_malloc_error();
	new->value = NULL;
	new->token = 0;
	new->std = 0;
	new->heredoc = NULL;
	new->next = NULL;
	new->right = NULL;
	new->left = NULL;
	return (new);
}
