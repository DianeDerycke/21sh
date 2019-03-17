/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 00:58:27 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/17 00:59:43 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/error.h"

int 	unexpected_eof(void)
{
	ft_putendl_fd("21sh: syntax error: unexpected end of file", 2);
	return (FAILURE);
}

int			syntax_error(char *str)
{
	ft_putstr_fd("21sh: syntax error near unexpected token ", 2);
	if (!str)
		ft_putendl_fd("'newline'", 2);
	else
	{
		ft_putchar_fd('\'', 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("\'", 2);
	}
	return (FAILURE);
}

int			ambiguous_redirect(char *arg)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": ambiguous redirect", 2);
	return (ERROR);
}