/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 17:33:44 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/15 17:28:28 by dideryck         ###   ########.fr       */
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

int 	fork_error(void)
{
	ft_putendl_fd("21sh: error during process creation", 2);
	return (FAILURE);
}

int 	pipe_error(void)
{
	ft_putendl_fd("21sh: error during pipe creation", 2);
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
		return(error_chdir(ERROR, str, "21sh"));
	if (error_nb == ERRFORK)
		return (fork_error());
	if (error_nb == ERRPIPE)
		return (pipe_error());
    return (FAILURE);
}
