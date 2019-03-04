/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 17:33:44 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/04 18:15:16 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

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

int     get_error_lex(int error_nb, char *str)
{
    if (error_nb == UNEXPTOKEN)
        return (syntax_error(str));
    return (FAILURE);
}
