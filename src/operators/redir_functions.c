/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:26:14 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/21 18:04:10 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

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

static int		redir_null(void)
{
	int		fd;

	if ((fd = open("/dev/null", O_RDWR)) == ERROR)
		return (-2);
	return (fd);
}

int				handle_agregation(t_ast *redir)
{
	int		fd;
	int		is_close;

	fd = 0;
	is_close = 0;
	if ((fd = get_dest_fd(redir->left->value, &is_close)) == ERROR)
	{
		ambiguous_redirect(redir->left->value);
		return (-2);
	}
	if (is_close == 1)
		return (redir_null());
	return (fd);
}

t_ast			*find_next_redir(t_ast *ast)
{
	if (!ast)
		return (NULL);
	while (ast)
	{
		if (ast->token >= GREAT && ast->token <= GREATAND)
			return (ast);
		ast = ast->left;
	}
	return (NULL);
}

int				get_std_redir(t_ast *ast)
{
	if (ast->token == LESS || ast->token == LESSAND)
		return (ast->std == 0 ? STDIN_FILENO : ast->std);
	if (ast->token == GREATAND)
		return (ast->std == 0 ? STDOUT_FILENO : ast->std);
	if (ast->token == GREAT || ast->token == DGREAT)
		return (STDOUT_FILENO);
	if (ast->token == LESS || ast->token == DLESS)
		return (STDIN_FILENO);
	return (0);
}
