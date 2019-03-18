/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:26:14 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/18 15:26:57 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

int				get_io_number(t_ast *ast, t_ast *redir, int token)
{
	if (!ast || !redir)
		return (ERROR);
	if (ast == redir)
		return (token == GREATAND ? 1 : 0);
	while (ast->left && ast->left != redir)
		ast = ast->left;
	if (ast && ast->token == DIGIT && ast->io_number == 1)
		return (ft_atoi(ast->value));
	return (ERROR);
}

static int		get_dest_fd(char *arg, int *is_close)
{
	int		i;
	int		dest;
	char	*tmp;

	i = 0;
	dest = 0;
	tmp = NULL;
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	if (arg[i] && (arg[i] != '-' || (ft_strlen(arg) - (i + 1)) > 0))
		return (ERROR);
	if (arg[i] == '-' && !arg[i + 1])
		*is_close = 1;
	if (!(tmp = ft_strndup(arg, i)))
		return (ERROR);
	dest = ft_atoi(tmp);
	ft_strdel(&tmp);
	return (dest);
}

int				handle_agregation(t_ast *redir, t_ast *ast)
{
	int		io_nb;
	int		output;
	int		is_close;

	io_nb = 0;
	output = 0;
	is_close = 0;
	if ((output = get_dest_fd(redir->left->value, &is_close)) == ERROR)
	{
		ambiguous_redirect(redir->left->value);
		return (-2);
	}
	if ((io_nb = get_io_number(ast, redir, redir->token)) == ERROR)
		return (-2);
	if (redir->token == LESSAND)
		dup2(io_nb, output);
	else if (redir->token == GREATAND)
		dup2(output, io_nb);
	if (is_close == 1 && redir->token == GREATAND)
		close(io_nb);
	return (SUCCESS);
}
