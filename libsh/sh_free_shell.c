/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_free_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrandou <mrandou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:05:57 by DERYCKE           #+#    #+#             */
/*   Updated: 2019/03/17 16:59:57 by mrandou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsh.h"

void		sh_free_shell(t_sh *shell)
{
	if (!shell)
		return ;
	if (shell->cmd)
		ft_free_array(shell->cmd);
	if (shell->path)
		ft_strdel(&(shell->path));
	if (shell->env)
		ft_free_array(shell->env);
	free(shell);
	shell = NULL;
}
