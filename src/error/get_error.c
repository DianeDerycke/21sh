/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dideryck <dideryck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 17:33:44 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/18 14:58:34 by dideryck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/error.h"

int		fork_error(void)
{
	ft_putendl_fd("21sh: error during process creation", 2);
	return (FAILURE);
}

int		pipe_error(void)
{
	ft_putendl_fd("21sh: error during pipe creation", 2);
	return (FAILURE);
}

int		get_error(int error_nb, char *str)
{
	if (error_nb == UNEXPTOKEN)
		return (syntax_error(str));
	if (error_nb == UNDEFVAR)
		return (sh_undefined_variable(str));
	if (error_nb == CNOTFOUND)
		return (sh_command_not_found(str));
	if (error_nb == PERMDENIED)
		return (sh_perm_denied(str));
	if (error_nb == UNEXPEOF)
		return (unexpected_eof());
	if (error_nb == NOFILEDIR)
		return (error_chdir(ERROR, str, "21sh"));
	if (error_nb == ERRFORK)
		return (fork_error());
	if (error_nb == ERRPIPE)
		return (pipe_error());
	if (error_nb == NOTERM)
		ft_putendl_fd("21sh: Variable TERM is unvalid.", 2);
	if (error_nb == ERRSIZE)
		ft_putendl_fd(str, 2);
	return (FAILURE);
}
