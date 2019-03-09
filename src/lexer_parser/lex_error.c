/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: DERYCKE <DERYCKE@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 17:33:44 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/08 16:50:45 by DERYCKE          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh21.h"

char 	*getter_error_var(char *str)
{
	static char *error_var = NULL;
	
	if (str)
		error_var = str;
	return (error_var);
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

int 	unexpected_eof(void)
{
	ft_putendl_fd("21sh: syntax error: unexpected end of file", 2);
	return (FAILURE);
}

int     get_error(int error_nb, char *str)
{
    if (error_nb == UNEXPTOKEN)
        return (syntax_error(str));
	if (error_nb == UNDEFVAR)
		return(ms_undefined_variable(str));
	if (error_nb == CNOTFOUND)
		return(ms_command_not_found(str));
	if (error_nb == PERMDENIED)
		return(ms_perm_denied(str));
	if (error_nb == UNEXPEOF)
		return (unexpected_eof());
	if (error_nb == NOFILEDIR)
		return(ms_no_such_file_or_dir("21sh", str));
    return (FAILURE);
}
